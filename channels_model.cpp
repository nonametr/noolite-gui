#include "channels_model.h"

QHash<int, QByteArray> ChannelsModel::role_fields =
{
    { ChannelsModel::NameField, "text" },
    { ChannelsModel::ChannelField, "channel" }
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

QHash<QByteArray, int> ChannelsModel::field_roles = mirror_map(role_fields);

Channel::Channel(const QString &v_name, const qint32 &v_channel) : _name(v_name), _channel(v_channel)
{}

QString Channel::name() const
{
    return _name;
}

qint32 Channel::channel() const
{
    return _channel;
}

void Channel::setName(const QString &v_name)
{
    _name = v_name;
}

void Channel::setChannel(const qint32 &v_channel)
{
    _channel = v_channel;
}

ChannelsModel::ChannelsModel(QObject *parent) : QAbstractListModel(parent)
{
}

void ChannelsModel::addChannel(const Channel &v_console)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _channels << v_console;
    endInsertRows();
}

int ChannelsModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return _channels.count();
}

QVariant ChannelsModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= _channels.count())
        return QVariant();

    const Channel &channel = _channels[index.row()];
    if (role == NameField)
        return channel.name();
    else if (role == ChannelField)
        return channel.channel();
    return QVariant();
}

bool ChannelsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Channel &console = _channels[index.row()];

    if (role == NameField)
        console.setName(value.toString());
    else if (role == ChannelField)
        console.setChannel(value.toInt());

    return true;
}

bool ChannelsModel::setProperty(int row, QString propertyName, QVariant propertyValue)
{
    return setData(this->index(row), propertyValue, field_roles.find(propertyName.toStdString().c_str()).value());
}

QHash<int, QByteArray> ChannelsModel::roleNames() const
{
    return role_fields;
}
