#ifndef STATUSMODEL_H
#define STATUSMODEL_H

#include "qobject.h"

class RxStatusModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool active READ activeRead WRITE setActive NOTIFY activeUpdate)
    Q_PROPERTY(QString channel READ channelRead NOTIFY channelUpdate)
    Q_PROPERTY(QString action READ actionRead NOTIFY actionUpdate)
    Q_PROPERTY(QString togl READ toglRead NOTIFY toglUpdate)

    Q_PROPERTY(QString data0 READ data0Read NOTIFY data0Update)
    Q_PROPERTY(QString data1 READ data1Read NOTIFY data1Update)
    Q_PROPERTY(QString data2 READ data2Read NOTIFY data2Update)
    Q_PROPERTY(QString data3 READ data3Read NOTIFY data3Update)

public:
    RxStatusModel() = default;
    virtual ~RxStatusModel() override = default;

    bool activeRead() const;
    QString channelRead() const;
    QString actionRead() const;
    QString toglRead() const;
    QString data0Read() const;
    QString data1Read() const;
    QString data2Read() const;
    QString data3Read() const;

    void setActive(bool new_active);
    void setChannel(int new_channel);
    void setAction(int new_action);
    void setTogl(int new_togl);
    void setData0(int new_data);
    void setData1(int new_data);
    void setData2(int new_data);
    void setData3(int new_data);

signals:
    void activeUpdate();
    void channelUpdate();
    void actionUpdate();
    void toglUpdate();
    void data0Update();
    void data1Update();
    void data2Update();
    void data3Update();

private:
    bool _active = true;
    QString _channel;
    QString _action;
    QString _togl;
    QString _data0;
    QString _data1;
    QString _data2;
    QString _data3;
};

#endif // STATUSMODEL_H
