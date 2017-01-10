#ifndef CPPCONTROLLER_H
#define CPPCONTROLLER_H

#include <QObject>
#include <QApplication>
#include <QTranslator>
#include <QQmlApplicationEngine>

#include <map>
#include <libusb-1.0/libusb.h>

#include "config.h"
#include "channels_model.h"
#include "common.h"
#include "../noolite-rx/rx2164.h"
#include "status_model.h"

using namespace std;

#define LANG_ENGLISH 1
#define LANG_RUSSIAN 2
#define LANG_UKRAINIAN 3

class CPPController : public QObject
{
   Q_OBJECT

public:
   CPPController();
   virtual ~CPPController() override;

   RX2164_STATE rxStart();
   void reloadWindow();
   void setEngine(QQmlApplicationEngine &l_engine);

public slots:
   void onSave();
   void onLanguageChanged(const int new_lang);
   void onBind(const int ch_id);
   void onUnbind(const int ch_id);
   void onChannelSelect(const int ch_id, const int act_id);
   void onEvent(int new_togl, int action, int channel, int data_format);


private:
    RX2164 rx;
    Config config;
    QTranslator en_translator;
    QTranslator ru_translator;
    QTranslator ua_translator;

    QTranslator *current_translator = nullptr;
    map<int, QTranslator*> translator_map;
    map<int, QString> lang_map;

    QQmlContext *_context = nullptr;
    QQmlApplicationEngine *engine = nullptr;

    StatusModel _status_model;
    ChannelsModel _channels_model;
    ChannelCfgModel _channel_cfg_model;

    void _setLanguage(const int new_lang);
};

#endif // CPPCONTROLLER_H
