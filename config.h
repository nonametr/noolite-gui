#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include <QJsonDocument>
#include <QJsonObject>

using namespace std;

class Config
{
public:
    Config() = default;
    ~Config() = default;

    int getLang();
    void setLang(int lang_id);

private:
    void _createDummyConfig(const string str_file);
    char* _readFile(const string str_file);
    int _getSystemLanguage();

    QJsonDocument j_doc;

    static const string _config_path;
};

#endif // CONFIG_H
