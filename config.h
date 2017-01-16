#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "rx-gui/rx_channels_model.h"
#include "rx-gui/rx_channel_cfg_model.h"
#include "rx-gui/rx_gui_model.h"

#include "tx-gui/tx_channels_model.h"
#include "tx-gui/tx_gui_model.h"

using namespace std;

#define TRX_LANG_ENGLISH 1
#define TRX_LANG_RUSSIAN 2
#define TRX_LANG_UKRAINIAN 3

class Config
{
public:
    Config();
    ~Config() = default;

    int getLang();
    void setLang(int lang_id);
    void save();    

    void setRxGuiModel(RxGUIModel *rx_gui_model);
    void setRxChannelsModel(RxChannelsModel *channels_model);

    void setTxChannelsModel(TxChannelsModel *channels_model);
    void setTxGuiModel(TxGUIModel *tx_gui_model);

    void setCurrentWindow(QString name);

    TxGUIModel getTxGuiModel();
    TxChannelsModel getTxChannelsModel();

    RxChannelsModel getRxChannelsModel();
    RxGUIModel getRxGuiModel();

    QString getCurrentWindow();

    pair<int, int> getRxHW();
    pair<int, int> getTxHW();
    pair<int, int> getRxXY();
    pair<int, int> getTxXY();
    void setRxHW(int h, int w);
    void setTxHW(int h, int w);
    void setRxXY(int x, int y);
    void setTxXY(int x, int y);

private:
    void _createDummyConfig();
    QByteArray _readFile(const QString str_file);
    int _getSystemLanguage();

    QJsonArray j_tx_channels;
    QJsonArray j_rx_channels;
    QJsonObject j_win;

    static const QString _config_path;
};

#endif // CONFIG_H
