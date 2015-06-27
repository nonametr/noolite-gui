#include "config.h"
#include "cpp_controller.h"

#include <QLocale>
#include <QDebug>
#include <QFile>

const string Config::_config_path = "rx_config.ini";

int Config::getLang()
{
    char *file_data = _readFile(_config_path.c_str());
    j_doc = QJsonDocument::fromJson(file_data);
    free(file_data);
    QJsonObject j_config = j_doc.object();
    uint lang_id = j_config["lang"].toInt();

    switch(lang_id)
    {
    case LANG_ENGLISH:
    case LANG_RUSSIAN:
    case LANG_UKRAINIAN:
        return lang_id;
    default:
        _createDummyConfig(_config_path);
        return getLang();
    }
}

void Config::setLang(int lang_id)
{
    QFile file(_config_path.c_str());
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    QJsonObject j_config = j_doc.object();
    j_config["lang"] = lang_id;

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
    string lang_str = std::to_string(_getSystemLanguage());
    string text = "{\"lang\":" + lang_str + "}";
    FILE *fp = fopen(str_file.c_str(), "wt");
    fwrite(text.c_str(), text.length(), 1, fp);
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
