#include "cpp_controller.h"

#include <QDebug>
#include <QQmlContext>
#include <QMessageBox>
#include <QQuickWindow>
#include <QtConcurrent/QtConcurrent>
#include <QAbstractButton>

#include <functional>

CPPController::CPPController()
{
    ASSERT_WITH_CODE(!libusb_init(nullptr), "Can't init. libusb", exit(1));

    ua_translator.load("ukrainian.qm", ":/translations");
    en_translator.load("english.qm", ":/translations");
    ru_translator.load("russian.qm", ":/translations");

    translator_map =
    {
        {LANG_ENGLISH,      &en_translator},
        {LANG_RUSSIAN,      &ru_translator},
        {LANG_UKRAINIAN,    &ua_translator}
    };

    lang_map =
    {
        {LANG_ENGLISH,      "English"},
        {LANG_RUSSIAN,      "Russian"},
        {LANG_UKRAINIAN,    "Ukrainian"}
    };

    rxStart();
}

CPPController::~CPPController()
{
    rx.close();
    libusb_exit(nullptr);
}

RX2164_STATE CPPController::rxStart()
{
    ASSERT_WITH_CODE(rx.state() != LOOPING, return LOOPING);

    std::function<void(int, int, int, int)> callback = std::bind(&CPPController::onEvent, this,
                                                std::placeholders::_1, std::placeholders::_2,
                                                std::placeholders::_3, std::placeholders::_4);//a call of std::bind

    rx.init(callback);
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
    config.setChannelsModel();
    config.save();
}

void CPPController::onLanguageChanged(const int new_lang)
{
    _setLanguage(new_lang);
    reloadWindow();
    config.setLang(new_lang);
}

void CPPController::onEvent(int new_togl, int action, int channel, int data_format)
{
    ASSERT_WITH_CODE(_context && _status_model.activeRead(), return);

    _status_model.setTogl(new_togl);
    _status_model.setAction(action);
    _status_model.setChannel(channel);
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
    engine->clearComponentCache();

    _context = engine->rootContext();

    _context->setContextProperty("cpp_model_channels", &config.getChannelsModel());
    _context->setContextProperty("cpp_model_channel_actions", &config.getChannelActionsModel(0));
    _context->setContextProperty("cpp_model_status", &_status_model);

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
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
