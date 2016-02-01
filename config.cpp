#include "config.h"
#include "cpp_controller.h"

#include <QLocale>
#include <QDebug>
#include <QFile>

const string Config::_config_path = "rx_config.ini";

Config::Config()
{
    _channels_actions_model.resize(RX2164_MAX_CHANNELS);
    char *file_data = _readFile(_config_path.c_str());
    j_doc = QJsonDocument::fromJson(file_data);
    free(file_data);
}

ChannelsModel &Config::getChannelsModel()
{
    ASSERT_WITH_CODE(!_channels_model.rowCount(), return _channels_model);

    uint channel_id = -1;
    QJsonArray j_channels = j_doc.object()["channels"].toArray();
    for(QJsonValue j_channel : j_channels)
    {
        _channels_model.addChannel(Channel(j_channel.toObject()["name"].toString(), ++channel_id));
    }

    return _channels_model;
}

ChannelActions &Config::getChannelActionsModel(qint32 channel_id)
{
    return _channels_actions_model[channel_id];
}

void Config::setChannelsModel(ChannelsModel *channels_model)
{
    if(!channels_model)
        channels_model = &_channels_model;

    QList<Channel> &channels = channels_model->getChannels();
    j_channels = j_doc.object()["channels"].toArray();
    for(Channel &channel : channels)
    {
        QJsonObject j_channel = j_channels[channel.channel()].toObject();

        j_channel["name"] = channel.name();
        j_channels[channel.channel()] = j_channel;
    }
}

int Config::getLang()
{
    ASSERT_WITH_CODE(!_lang_id, return _lang_id);

    QJsonObject j_config = j_doc.object();
    j_lang = j_config["lang"];
    _lang_id = j_lang.toInt();

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
    j_lang = _lang_id;
}

void Config::save()
{
    QFile file(_config_path.c_str());
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    //set lang
    QJsonObject j_config = j_doc.object();
    j_config["lang"] = j_lang;

    //set chgannel
    j_config["channels"] = j_channels;

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
    QJsonArray json_actions;
    for(int action_id = 0; action_id < MAX_ACTIONS; ++action_id)
    {
        QJsonObject json_action;
        json_action.insert("script", "~/noolite-daemon.sh");
        json_action.insert("forward_params", QJsonValue(true));
        json_action.insert("forward_ext", QJsonValue(false));
        json_actions.push_back(json_action);
    }

    QJsonArray json_channels;
    for(int channel_id = 0; channel_id < 64; ++channel_id)
    {
        QJsonObject json_channel;
        json_channel.insert("name", QJsonValue(QString("channel #") + QString::number(channel_id)));
        json_channel.insert("actions", QJsonValue(json_actions));
        json_channels.push_back(json_channel);
    }

    QJsonObject json_obj;
    json_obj.insert("lang", QJsonValue(_getSystemLanguage()));
    json_obj.insert("channels", json_channels);

    j_doc = QJsonDocument(json_obj);
    FILE *fp = fopen(str_file.c_str(), "wt");
    string json_str = j_doc.toJson().toStdString();
    fwrite(json_str.c_str(), json_str.length(), 1, fp);
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
        _readFile(str_file);
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
