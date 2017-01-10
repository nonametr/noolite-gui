#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "channels_model.h"
#include "channel_cfg_model.h"

using namespace std;

class Config
{
public:
    Config();
    ~Config() = default;

    int getLang();
    void setLang(int lang_id);
    void save();

    ChannelsModel &getChannelsModel();
    void setChannelsModel(ChannelsModel *channels_model = nullptr);

private:
    void _createDummyConfig(const string str_file);
    char* _readFile(const string str_file);
    int _getSystemLanguage();

    QJsonDocument j_doc;
    QJsonArray j_channels;
    QJsonValue j_lang;

    int _lang_id = 0;
    ChannelsModel _channels_model;

    static const string _config_path;
};

#endif // CONFIG_H
