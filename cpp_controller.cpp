#include "cpp_controller.h"

#include <QDebug>
#include <QQmlContext>
#include <QMessageBox>
#include <QQuickWindow>
#include <QtConcurrent/QtConcurrent>
#include <QAbstractButton>

#include <functional>

#define TRX_LANG_ENGLISH 1
#define TRX_LANG_RUSSIAN 2
#define TRX_LANG_UKRAINIAN 3

CPPController::CPPController()
{
    ASSERT_WITH_CODE(!libusb_init(nullptr), "Can't init. libusb", exit(1));

    rxStart();
}

void CPPController::initGUI()
{
    ua_translator.load("ukrainian.qm", ":/translations");
    en_translator.load("english.qm", ":/translations");
    ru_translator.load("russian.qm", ":/translations");

    translator_map =
    {
        {TRX_LANG_ENGLISH,      &en_translator},
        {TRX_LANG_RUSSIAN,      &ru_translator},
        {TRX_LANG_UKRAINIAN,    &ua_translator}
    };

    lang_map =
    {
        {TRX_LANG_ENGLISH,      "English"},
        {TRX_LANG_RUSSIAN,      "Russian"},
        {TRX_LANG_UKRAINIAN,    "Ukrainian"}
    };

    _currentWindow = config.getCurrentWindow();
    _rx_gui_model = config.getRxGuiModel();
    _rx_channels_model = config.getRxChannelsModel();

    _tx_channels_model = config.getTxChannelsModel();
    _tx_gui_model = config.getTxGuiModel();
}

CPPController::~CPPController()
{
    rx.close();
    libusb_exit(nullptr);
}

RX2164_STATE CPPController::rxStart()
{
    ASSERT_WITH_CODE(rx.state() != LOOPING, return LOOPING);

    std::function<void(int, int, int, int, u_char, u_char, u_char, u_char)> callback = std::bind(&CPPController::onEvent, this,
                                                std::placeholders::_1, std::placeholders::_2,
                                                std::placeholders::_3, std::placeholders::_4,
                                                                 std::placeholders::_5, std::placeholders::_6,
                                                                 std::placeholders::_7, std::placeholders::_8);

    map<channelId, map<actionId, RxActionData>> _channel_actions;

    RxChannelsModel rxChannels = config.getRxChannelsModel();
    for(RxChannel &channel : rxChannels.getChannels())
    {
        for(int i = 0; i < channel.channelActions().size(); ++i)
        {
            RxChannelCfgModel &channelModel = channel.channelActions()[i];
            RxActionData &channelAction = _channel_actions[channel.channel()][i];

            channelAction.script = channelModel.scriptRead().toStdString();
            channelAction.fw = channelModel.fwRead();
            channelAction.fw_ext = channelModel.fwExtRead();
        }
    }

    rx.init(_channel_actions, callback);
    ASSERT_WITH_CODE(rx.open() == RX2164_STATE::OPENED, QMessageBox::critical(nullptr, tr("Error"), tr("Failed to open RX2164")); return CLOSED);
    ASSERT_WITH_CODE(rx.start() == RX2164_STATE::LOOPING, QMessageBox::critical(nullptr, tr("Error"), tr("Failed to start quering loop on RX2164")); return CLOSED);

    return LOOPING;
}

void CPPController::setEngine(QQmlApplicationEngine &l_engine)
{
    engine = &l_engine;
    _setLanguage(config.getLang());
}

void CPPController::onSave()
{
    config.setRxGuiModel(&_rx_gui_model);
    config.setTxGuiModel(&_tx_gui_model);
    config.setRxChannelsModel(&_rx_channels_model);
    config.setTxChannelsModel(&_tx_channels_model);
    config.save();
}

void CPPController::onLanguageChanged(const int new_lang)
{
    _setLanguage(new_lang);
    reloadWindow();
    config.setLang(new_lang);
}

void CPPController::onToolChanged(QString windowName)
{
    _currentWindow = windowName;
    reloadWindow();
}

void CPPController::onEvent(int new_togl, int action, int channel, int data_format, u_char d0, u_char d1, u_char d2, u_char d3)
{
    ASSERT_WITH_CODE(_context && _rx_status_model.activeRead(), return);

    _rx_status_model.setTogl(new_togl);
    _rx_status_model.setAction(action);
    _rx_status_model.setChannel(channel, _rx_channels_model.getChannels()[channel].name());
    _rx_status_model.setDf(data_format);
    _rx_status_model.setData0(d0);
    _rx_status_model.setData1(d1);
    _rx_status_model.setData2(d2);
    _rx_status_model.setData3(d3);
}

void CPPController::onTxExecute(const int ch_id, const int action_id, const int v1, const int v2, const int v3)
{
    tx.execute(static_cast<TX_ACTION>(action_id), static_cast<u_char>(ch_id), static_cast<u_char>(v1), static_cast<u_char>(v2), static_cast<u_char>(v3));
}

void CPPController::onChannelSelect(const int ch_id, const int act_id)
{
    engine->rootContext()->setContextProperty("rx_model_channel_cfg", &_rx_channels_model.getChannels()[ch_id].channelActions()[act_id]);

    qDebug() << "ch:" << ch_id << "act:" << act_id;
}

void CPPController::onUnbind(const int ch_id)
{
    ASSERT_WITH_CODE(rxStart() == LOOPING, QMessageBox::critical(nullptr, tr("Error"), tr("RX2164 not ready!")); return);

    rx.unbindChannel(ch_id);
}

void CPPController::onBind(const int ch_id)
{
    ASSERT_WITH_CODE(rxStart() == LOOPING, QMessageBox::critical(nullptr, tr("Error"), tr("RX2164 not ready!")); return);

    bool binding_canceled = false;
    QFuture<void> bind_future = QtConcurrent::run([&]() -> void
    {
        rx.bindChannel(ch_id);
        rx.waitForEvent(BIND, 40 * 1000000);
    });

    QObject *topLevel = engine->rootObjects().back();
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    window->hide();

    QMessageBox msgBox(nullptr);
    msgBox.setText(tr("Binding, please wait..."));
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setWindowFlags(Qt::CustomizeWindowHint);
    QAbstractButton *button_obj = msgBox.buttons().value(0);
    QObject::connect(button_obj, &QAbstractButton::clicked, [&](){ binding_canceled = true; rx.stopBind(); rx.stopWaitForEvent(); window->show(); });
    msgBox.show();

    do
    {
        QApplication::processEvents();
        QThread::usleep(1000);
    } while(bind_future.isRunning());

    if(!binding_canceled)
    {
        msgBox.close();
        window->show();
    }
}

void CPPController::reloadWindow()
{
    engine->load(QUrl(_currentWindow));
}

void CPPController::loadWindow()
{
    engine->clearComponentCache();

    _context = engine->rootContext();

    _context->setContextProperty("rx_model_gui", &_rx_gui_model);
    _context->setContextProperty("rx_model_channels", &_rx_channels_model);
    _context->setContextProperty("rx_model_channel_cfg", &_rx_channel_cfg_model);
    _context->setContextProperty("rx_model_status", &_rx_status_model);

    _context->setContextProperty("tx_model_gui", &_tx_gui_model);
    _context->setContextProperty("tx_model_channels", &_tx_channels_model);

    engine->load(QUrl(_currentWindow));
}

void CPPController::_setLanguage(const int new_lang)
{
    qDebug() << "Switching language to " << lang_map[new_lang].toStdString().c_str();

    auto it_translation = translator_map.find(new_lang);
    if(it_translation == translator_map.end())
    {
        qDebug() << "Unsupported language";
        return;
    }

    qApp->removeTranslator(current_translator);
    current_translator = it_translation->second;
    qApp->installTranslator(current_translator);
}
