#ifndef CPPCONTROLLER_H
#define CPPCONTROLLER_H

#include <QObject>
#include <QApplication>
#include <QTranslator>
#include <QQmlApplicationEngine>

#include <map>
#include <libusb-1.0/libusb.h>

#include "config.h"
#include "common.h"
#include "noolite-rx/rx2164.h"
#include "noolite-tx/tx1132.h"

#include "rx-gui/rx_channels_model.h"
#include "rx-gui/rx_status_model.h"
#include "rx-gui/rx_gui_model.h"

#include "tx-gui/tx_channels_model.h"
#include "tx-gui/tx_gui_model.h"

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
   void loadWindow();
   void setEngine(QQmlApplicationEngine &l_engine);

public slots:
    void onSave();
    void onLanguageChanged(const int new_lang);
    void onToolChanged(QString windowName);
    void onBind(const int ch_id);
    void onUnbind(const int ch_id);
    void onChannelSelect(const int ch_id, const int act_id);
    void onEvent(int new_togl, int action, int channel, int data_format);
    void onTxExecute(const int ch_id, const int action_id, const int v1, const int v2, const int v3);

private:
    Tx1132 tx;
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

    RxStatusModel _rx_status_model;
    RxChannelsModel _rx_channels_model;
    RxChannelCfgModel _rx_channel_cfg_model;
    RxGUIModel _rx_gui_model;

    TxChannelsModel _tx_channels_model;
    TxGUIModel _tx_gui_model;
    QString _currentWindow = "qrc:/RxTool.qml";

    void _setLanguage(const int new_lang);
};

#endif // CPPCONTROLLER_H
