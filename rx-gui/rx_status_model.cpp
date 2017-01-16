#include "rx_status_model.h"
#include "noolite-trx/defs.h"
#include "noolite-trx/defs_to_str.h"

bool RxStatusModel::activeRead() const
{
    return _active;
}

QString RxStatusModel::channelRead() const
{
    return _channel;
}

QString RxStatusModel::actionRead() const
{
    return _action;
}

QString RxStatusModel::toglRead() const
{
    return _togl;
}

QString RxStatusModel::dfRead() const
{
    return _df;
}

QString RxStatusModel::data0Read() const
{
    return _data0;
}

QString RxStatusModel::data1Read() const
{
    return _data1;
}

QString RxStatusModel::data2Read() const
{
    return _data2;
}

QString RxStatusModel::data3Read() const
{
    return _data3;
}

void RxStatusModel::setActive(bool new_active)
{
    _active = new_active;
    emit activeUpdate();
}

void RxStatusModel::setChannel(int new_channel, QString channel_name)
{
    _channel = "[" + QString::number(new_channel) + "]" + channel_name;
    emit channelUpdate();
}

void RxStatusModel::setAction(int new_action)
{
    _action = QString::fromStdString(_actionToStr(new_action)) + QString("[") + QString::number(new_action) + QString("]");
    emit actionUpdate();
}

void RxStatusModel::setTogl(int new_togl)
{
    _togl = QString::number(new_togl);
    emit toglUpdate();
}

void RxStatusModel::setDf(int new_df)
{
    _df = QString::number(new_df);
    emit dfUpdate();
}

void RxStatusModel::setData0(int new_data)
{
    _data0 = QString::number(new_data);
    emit data0Update();
}

void RxStatusModel::setData1(int new_data)
{
    _data1 = QString::number(new_data);
    emit data1Update();
}

void RxStatusModel::setData2(int new_data)
{
    _data2 = QString::number(new_data);
    emit data2Update();
}

void RxStatusModel::setData3(int new_data)
{
    _data3 = QString::number(new_data);
    emit data3Update();
}
