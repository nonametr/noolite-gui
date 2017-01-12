#include "tx_channels_model.h"

QHash<int, QByteArray> TxChannelsModel::role_fields =
{
    { TxChannelsModel::NameField, "text" },
    { TxChannelsModel::ChannelField, "channel" }
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

QHash<QByteArray, int> TxChannelsModel::field_roles = mirror_map(role_fields);

TxChannel::TxChannel(const QString &v_name, const qint32 &v_channel) : _name(v_name), _channel(v_channel)
{}

QString TxChannel::name() const
{
    return _name;
}

qint32 TxChannel::channel() const
{
    return _channel;
}

void TxChannel::setName(const QString &v_name)
{
    _name = v_name;
}

void TxChannel::setChannel(const qint32 &v_channel)
{
    _channel = v_channel;
}

TxChannelsModel::TxChannelsModel(QObject *parent) : QAbstractListModel(parent)
{
}

void TxChannelsModel::addChannel(const TxChannel &v_console)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _channels << v_console;
    endInsertRows();
}

int TxChannelsModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return _channels.count();
}

QVariant TxChannelsModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= _channels.count())
        return QVariant();

    const TxChannel &channel = _channels[index.row()];
    if (role == NameField)
        return channel.name();
    else if (role == ChannelField)
        return channel.channel();

    return QVariant();
}

bool TxChannelsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    TxChannel &console = _channels[index.row()];

    if (role == NameField)
        console.setName(value.toString());
    else if (role == ChannelField)
        console.setChannel(value.toInt());

    return true;
}

bool TxChannelsModel::setProperty(int row, QString propertyName, QVariant propertyValue)
{
    return setData(this->index(row), propertyValue, field_roles.find(propertyName.toStdString().c_str()).value());
}

QHash<int, QByteArray> TxChannelsModel::roleNames() const
{
    return role_fields;
}
