#include "rx_channels_model.h"

QHash<int, QByteArray> RxChannelsModel::role_fields =
{
    { RxChannelsModel::NameField, "text" },
    { RxChannelsModel::ChannelField, "channel" }
};

static QHash<QByteArray, int> mirror_map(QHash<int, QByteArray> &original_map)
{
    QHash<QByteArray, int> result;

    QHashIterator<int, QByteArray> it(original_map);
    while (it.hasNext()) {
        it.next();
        result[it.value()] = it.key();
    }

    return result;
}

QHash<QByteArray, int> RxChannelsModel::field_roles = mirror_map(role_fields);

RxChannel::RxChannel(const QString &v_name, const qint32 &v_channel, QList<RxChannelCfgModel> &v_channelActions) : _name(v_name), _channel(v_channel), _channelActions(v_channelActions)
{}

QString RxChannel::name() const
{
    return _name;
}

qint32 RxChannel::channel() const
{
    return _channel;
}

QList<RxChannelCfgModel> &RxChannel::channelActions()
{
    return _channelActions;
}

void RxChannel::setName(const QString &v_name)
{
    _name = v_name;
}

void RxChannel::setChannel(const qint32 &v_channel)
{
    _channel = v_channel;
}

void RxChannel::setChannelActions(const QList<RxChannelCfgModel> &v_channelActions)
{
    _channelActions = v_channelActions;
}

RxChannelsModel::RxChannelsModel(QObject *parent) : QAbstractListModel(parent)
{
}

void RxChannelsModel::addChannel(const RxChannel &v_console)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _channels << v_console;
    endInsertRows();
}

int RxChannelsModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return _channels.count();
}

QVariant RxChannelsModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= _channels.count())
        return QVariant();

    const RxChannel &channel = _channels[index.row()];
    if (role == NameField)
        return channel.name();
    else if (role == ChannelField)
        return channel.channel();

    return QVariant();
}

bool RxChannelsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    RxChannel &console = _channels[index.row()];

    if (role == NameField)
        console.setName(value.toString());
    else if (role == ChannelField)
        console.setChannel(value.toInt());

    return true;
}

bool RxChannelsModel::setProperty(int row, QString propertyName, QVariant propertyValue)
{
    return setData(this->index(row), propertyValue, field_roles.find(propertyName.toStdString().c_str()).value());
}

QHash<int, QByteArray> RxChannelsModel::roleNames() const
{
    return role_fields;
}
