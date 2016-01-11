#include "status_model.h"
#include "../noolite-rx/defs.h"
#include "../noolite-rx/defs_to_str.h"

bool StatusModel::activeRead() const
{
    return _active;
}

QString StatusModel::channelRead() const
{
    return _channel;
}

QString StatusModel::actionRead() const
{
    return _action;
}

QString StatusModel::toglRead() const
{
    return _togl;
}

QString StatusModel::data0Read() const
{
    return _data0;
}

QString StatusModel::data1Read() const
{
    return _data1;
}

QString StatusModel::data2Read() const
{
    return _data2;
}

QString StatusModel::data3Read() const
{
    return _data3;
}

void StatusModel::setActive(bool new_active)
{
    _active = new_active;
    emit activeUpdate();
}

void StatusModel::setChannel(int new_channel)
{
    _channel = QString::number(new_channel);
    emit channelUpdate();
}

void StatusModel::setAction(int new_action)
{
    _action = QString::fromStdString(_actionToStr(new_action)) + QString("[") + QString::number(new_action) + QString("]");
    emit actionUpdate();
}

void StatusModel::setTogl(int new_togl)
{
    _togl = QString::number(new_togl);
    emit toglUpdate();
}

void StatusModel::setData0(int new_data)
{
    _data0 = QString::number(new_data);
    emit data0Update();
}

void StatusModel::setData1(int new_data)
{
    _data1 = QString::number(new_data);
    emit data1Update();
}

void StatusModel::setData2(int new_data)
{
    _data2 = QString::number(new_data);
    emit data2Update();
}

void StatusModel::setData3(int new_data)
{
    _data3 = QString::number(new_data);
    emit data3Update();
}
