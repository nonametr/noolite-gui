#include "config.h"
#include "cpp_controller.h"

#include <QLocale>
#include <QDebug>
#include <QFile>

const string Config::_config_path = "rx_config.ini";

Config::Config()
{
    char *file_data = _readFile(_config_path.c_str());
    j_doc = QJsonDocument::fromJson(file_data);
    free(file_data);
}

QString Config::getCurrentWindow()
{
    j_win = j_doc.object()["gui"].toObject();

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
    QJsonArray j_channels = j_doc.object()["tx_channels"].toArray();
    for(QJsonValue j_channel : j_channels)
    {
        _channels_model.addChannel(TxChannel(j_channel.toObject()["name"].toString(), ++channel_id));
    }

    return _channels_model;
}

RxChannelsModel Config::getRxChannelsModel()
{
    RxChannelsModel _channels_model;

    int channel_id = -1;
    QJsonArray j_channels = j_doc.object()["rx_channels"].toArray();
    for(QJsonValue j_channel : j_channels)
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
    j_tx_channels = j_doc.object()["rx_channels"].toArray();
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
    j_rx_channels = j_doc.object()["rx_channels"].toArray();
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
    j_win = j_doc.object()["gui"].toObject();

    return make_pair(j_win["rx"].toObject()["height"].toInt(), j_win["rx"].toObject()["width"].toInt());
}

pair<int, int> Config::getTxHW()
{
    j_win = j_doc.object()["gui"].toObject();

    return make_pair(j_win["tx"].toObject()["height"].toInt(), j_win["tx"].toObject()["width"].toInt());
}

pair<int, int> Config::getRxXY()
{
    j_win = j_doc.object()["gui"].toObject();

    return make_pair(j_win["rx"].toObject()["x"].toInt(), j_win["rx"].toObject()["y"].toInt());
}

pair<int, int> Config::getTxXY()
{
    j_win = j_doc.object()["gui"].toObject();

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
    ASSERT_WITH_CODE(!_lang_id, return _lang_id);

    j_win = j_doc.object()["gui"].toObject();
    _lang_id = j_win["lang"].toInt();

    switch(_lang_id)
    {
    case LANG_ENGLISH:
    case LANG_RUSSIAN:
    case LANG_UKRAINIAN:
        return _lang_id;
    default:
        _createDummyConfig(_config_path);
        return getLang();
    }
}

void Config::setLang(int lang_id)
{
    _lang_id = lang_id;
    j_win["lang"] = _lang_id;
}

void Config::save()
{
    QFile file(_config_path.c_str());
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    //set lang
    QJsonObject j_config = j_doc.object();

    //set channels
    j_config["rx_channels"] = j_rx_channels;
    j_config["tx_channels"] = j_tx_channels;

    //set tool windows
    j_config["gui"] = j_win;

    j_doc.setObject(j_config);
    out << j_doc.toJson();
}

int Config::_getSystemLanguage()
{
    QLocale::Country country = QLocale::system().country();

    qDebug() << "Selecting language for "<< QLocale::system().nativeCountryName();

    switch(country)
    {
    case QLocale::Ukraine:
        return LANG_UKRAINIAN;
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
        return LANG_RUSSIAN;
    default:
        return LANG_ENGLISH;
    }

    return LANG_ENGLISH;
}

void Config::_createDummyConfig(const string str_file)
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

    QJsonArray json_rx_channels;
    for(int channel_id = 0; channel_id < 64; ++channel_id)
    {
        QJsonObject json_channel;
        json_channel.insert("name", QJsonValue(QString("channel #") + QString::number(channel_id)));
        json_channel.insert("actions", QJsonValue(json_rx_actions));
        json_rx_channels.push_back(json_channel);
    }

    QJsonArray json_tx_channels;
    for(int channel_id = 0; channel_id < 64; ++channel_id)
    {
        QJsonObject json_channel;
        json_channel.insert("name", QJsonValue(QString("channel #") + QString::number(channel_id)));
        json_tx_channels.push_back(json_channel);
    }

    QJsonObject json_gui;
    QJsonObject json_rxgui;
    QJsonObject json_txgui;

    json_rxgui.insert("height", QJsonValue(480));
    json_rxgui.insert("width", QJsonValue(900));
    json_txgui.insert("height", QJsonValue(420));
    json_txgui.insert("width", QJsonValue(500));
    json_gui.insert("lang", QJsonValue(_getSystemLanguage()));
    json_gui.insert("rx", json_rxgui);
    json_gui.insert("tx", json_txgui);
    json_gui.insert("currentWindow", "qrc:/rx-gui/RxTool.qml");

    QJsonObject json_obj;
    json_obj.insert("rx_channels", json_rx_channels);
    json_obj.insert("tx_channels", json_tx_channels);
    json_obj.insert("gui", json_gui);

    j_doc = QJsonDocument(json_obj);
    FILE *fp = fopen(str_file.c_str(), "wt");
    string json_str = j_doc.toJson().toStdString();
    fwrite(json_str.c_str(), json_str.length(), 1, fp);
    fflush(fp);
    fclose(fp);
}

/**
 * @brief Config::readFile - reads file into memory
 * @param str_file - file path
 * @return file data
 */
char* Config::_readFile(const string str_file)
{
    char *buf = nullptr;
    FILE *fp;
    int len;

    fp = fopen(str_file.c_str(),"rt");

    if(!fp)
    {
        _createDummyConfig(str_file);
        return _readFile(str_file);
    }
    else
    {
        fseek(fp, 0, SEEK_END);
        len=ftell(fp) + 2;
        fseek(fp, 0, SEEK_SET);
        buf=(char *)malloc(len);
        memset(buf, 0, len);
        fread(buf, len, 1, fp);
        fclose(fp);
        qDebug() << "Loading configuration file from" << str_file.c_str();
    }

    return buf;
}
