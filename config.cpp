#include "config.h"
#include "cpp_controller.h"

#include <QLocale>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>

const QString Config::_config_path = QDir::homePath() + "/rx_config.ini";

Config::Config()
{
    QJsonDocument j_doc = QJsonDocument::fromJson(_readFile(_config_path));

    if(j_doc.isEmpty())
    {
        _createDummyConfig();
        j_doc = QJsonDocument::fromJson(_readFile(_config_path));
        if(j_doc.isEmpty())
        {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Failed to load configuration file!"));
            exit(EXIT_FAILURE);
        }
    }

    j_rx_channels = j_doc.object()["rx_channels"].toArray();
    j_tx_channels = j_doc.object()["tx_channels"].toArray();
    j_win = j_doc.object()["gui"].toObject();
}

QString Config::getCurrentWindow()
{
    return j_win["currentWindow"].toString();
}

RxGUIModel Config::getRxGuiModel()
{
    RxGUIModel rxGuiModel;

    rxGuiModel.rxXWrite(getRxXY().first);
    rxGuiModel.rxYWrite(getRxXY().second);
    rxGuiModel.rxHeightWrite(getRxHW().first);
    rxGuiModel.rxWidthWrite(getRxHW().second);

    return rxGuiModel;
}

TxGUIModel Config::getTxGuiModel()
{
    TxGUIModel txGuiModel;

    txGuiModel.txXWrite(getTxXY().first);
    txGuiModel.txYWrite(getTxXY().second);
    txGuiModel.txHeightWrite(getTxHW().first);
    txGuiModel.txWidthWrite(getTxHW().second);

    return txGuiModel;
}

TxChannelsModel Config::getTxChannelsModel()
{
    TxChannelsModel _channels_model;

    int channel_id = -1;
    for(QJsonValue j_channel : j_tx_channels)
    {
        _channels_model.addChannel(TxChannel(j_channel.toObject()["name"].toString(), ++channel_id));
    }

    return _channels_model;
}

RxChannelsModel Config::getRxChannelsModel()
{
    RxChannelsModel _channels_model;

    int channel_id = -1;
    for(QJsonValue j_channel : j_rx_channels)
    {
        QList<RxChannelCfgModel> channelActions;
        QJsonArray j_channelActions = j_channel.toObject()["actions"].toArray();
        for(QJsonValue j_action : j_channelActions)
        {
            QJsonObject j_obj = j_action.toObject();
            QString script = j_obj["script"].toString();
            bool fw = j_obj["forward_ext"].toBool();
            bool fwExt = j_obj["forward_params"].toBool();
            channelActions.append(RxChannelCfgModel(script, fw, fwExt));
        }
        _channels_model.addChannel(RxChannel(j_channel.toObject()["name"].toString(), ++channel_id, channelActions));
    }

    return _channels_model;
}

void Config::setCurrentWindow(QString name)
{
    j_win["currentWindow"] = name;
}

void Config::setTxGuiModel(TxGUIModel *tx_gui_model)
{
    setTxXY(tx_gui_model->txXRead(), tx_gui_model->txYRead());
    setTxHW(tx_gui_model->txHeightRead(), tx_gui_model->txWidthRead());
}

void Config::setRxGuiModel(RxGUIModel *rx_gui_model)
{
    setRxXY(rx_gui_model->rxXRead(), rx_gui_model->rxYRead());
    setRxHW(rx_gui_model->rxHeightRead(), rx_gui_model->rxWidthRead());
}

void Config::setTxChannelsModel(TxChannelsModel *channels_model)
{
    QList<TxChannel> &channels = channels_model->getChannels();

    for(TxChannel &channel : channels)
    {
        QJsonObject j_channel = j_tx_channels[channel.channel()].toObject();

        j_channel["name"] = channel.name();
        j_tx_channels[channel.channel()] = j_channel;
    }
}

void Config::setRxChannelsModel(RxChannelsModel *channels_model)
{
    QList<RxChannel> &channels = channels_model->getChannels();

    for(RxChannel &channel : channels)
    {
        QJsonObject j_channel = j_rx_channels[channel.channel()].toObject();

        QJsonArray j_channelAction;
        for(RxChannelCfgModel &channel_model : channel.channelActions())
        {
            QJsonObject j_action;
            j_action["forward_ext"] = channel_model.fwRead();
            j_action["forward_params"] = channel_model.fwExtRead();
            j_action["script"] = channel_model.scriptRead();
            j_channelAction.append(j_action);
        }

        j_channel["actions"] = j_channelAction;
        j_channel["name"] = channel.name();
        j_rx_channels[channel.channel()] = j_channel;
    }
}

pair<int, int> Config::getRxHW()
{
    return make_pair(j_win["rx"].toObject()["height"].toInt(), j_win["rx"].toObject()["width"].toInt());
}

pair<int, int> Config::getTxHW()
{
    return make_pair(j_win["tx"].toObject()["height"].toInt(), j_win["tx"].toObject()["width"].toInt());
}

pair<int, int> Config::getRxXY()
{
    return make_pair(j_win["rx"].toObject()["x"].toInt(), j_win["rx"].toObject()["y"].toInt());
}

pair<int, int> Config::getTxXY()
{
    return make_pair(j_win["tx"].toObject()["x"].toInt(), j_win["tx"].toObject()["y"].toInt());
}

void Config::setRxHW(int h, int w)
{
    QJsonObject params = j_win["rx"].toObject();
    params["height"] = QJsonValue(h);
    params["width"] = QJsonValue(w);

    j_win["rx"] = params;
}

void Config::setTxHW(int h, int w)
{
    QJsonObject params = j_win["tx"].toObject();
    params["height"] = QJsonValue(h);
    params["width"] = QJsonValue(w);

    j_win["tx"] = params;
}

void Config::setRxXY(int x, int y)
{
    QJsonObject params = j_win["rx"].toObject();
    params["x"] = QJsonValue(x);
    params["y"] = QJsonValue(y);

    j_win["rx"] = params;
}

void Config::setTxXY(int x, int y)
{
    QJsonObject params = j_win["tx"].toObject();
    params["x"] = QJsonValue(x);
    params["y"] = QJsonValue(y);

    j_win["tx"] = params;
}

int Config::getLang()
{
    return j_win["lang"].toInt();
}

void Config::setLang(int lang_id)
{
    j_win["lang"] = lang_id;
}

void Config::save()
{
    QFile file(_config_path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    QJsonDocument j_doc;
    QJsonObject j_config;

    //set channels
    j_config["rx_channels"] = j_rx_channels;
    j_config["tx_channels"] = j_tx_channels;

    //set tool windows
    j_config["gui"] = j_win;

    j_doc.setObject(j_config);
    out << j_doc.toJson();
    out.flush();
}

int Config::_getSystemLanguage()
{
    QLocale::Country country = QLocale::system().country();

    qDebug() << "Selecting language for "<< QLocale::system().nativeCountryName();

    switch(country)
    {
    case QLocale::Ukraine:
        return TRX_LANG_UKRAINIAN;
    case QLocale::Russia:
    case QLocale::Belarus:
    case QLocale::Kazakhstan:
    case QLocale::Latvia:
    case QLocale::Lithuania:
    case QLocale::Turkmenistan:
    case QLocale::Kirghiz:
    case QLocale::Moldova:
    case QLocale::Uzbekistan:
    case QLocale::Azerbaijani:
    case QLocale::ArmenianScript:
    case QLocale::Georgia:
        return TRX_LANG_RUSSIAN;
    default:
        return TRX_LANG_ENGLISH;
    }

    return TRX_LANG_ENGLISH;
}

void Config::_createDummyConfig()
{
    QJsonArray json_rx_actions;
    for(int action_id = 0; action_id < MAX_ACTIONS; ++action_id)
    {
        QJsonObject json_action;
        json_action.insert("script", "~/noolite-daemon.sh");
        json_action.insert("forward_params", QJsonValue(true));
        json_action.insert("forward_ext", QJsonValue(false));
        json_rx_actions.push_back(json_action);
    }

    for(int channel_id = 0; channel_id < 64; ++channel_id)
    {
        QJsonObject json_channel;
        json_channel.insert("name", QJsonValue(QString("channel #") + QString::number(channel_id)));
        json_channel.insert("actions", QJsonValue(json_rx_actions));
        j_rx_channels.push_back(json_channel);
    }

    for(int channel_id = 0; channel_id < 64; ++channel_id)
    {
        QJsonObject json_channel;
        json_channel.insert("name", QJsonValue(QString("channel #") + QString::number(channel_id)));
        j_tx_channels.push_back(json_channel);
    }

    QJsonObject json_rxgui;
    QJsonObject json_txgui;

    json_rxgui.insert("height", QJsonValue(480));
    json_rxgui.insert("width", QJsonValue(900));
    json_txgui.insert("height", QJsonValue(420));
    json_txgui.insert("width", QJsonValue(500));
    j_win.insert("lang", QJsonValue(_getSystemLanguage()));
    j_win.insert("rx", json_rxgui);
    j_win.insert("tx", json_txgui);
    j_win.insert("currentWindow", "qrc:/rx-gui/RxTool.qml");

    save();
}

/**
 * @brief Config::readFile - reads file into memory
 * @param str_file - file path
 * @return file data
 */
QByteArray Config::_readFile(const QString str_file)
{
    QByteArray result;

    QFile file(str_file);
    if (!file.open(QIODevice::ReadOnly))
        return QByteArray();

    result = file.readAll();
    file.close();

    return result;
}
