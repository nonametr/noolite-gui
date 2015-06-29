#include "consoles_model.h"

QHash<int, QByteArray> ConsolesModel::role_fields =
{
    { ConsolesModel::NameField, "text" },
    { ConsolesModel::ChannelField, "channel" }
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

QHash<QByteArray, int> ConsolesModel::field_roles = mirror_map(role_fields);

Console::Console(const QString &v_name, const qint32 &v_channel) : _name(v_name), _channel(v_channel)
{}

QString Console::name() const
{
    return _name;
}

qint32 Console::channel() const
{
    return _channel;
}

void Console::setName(const QString &v_name)
{
    _name = v_name;
}

void Console::setChannel(const qint32 &v_channel)
{
    _channel = v_channel;
}

ConsolesModel::ConsolesModel(QObject *parent) : QAbstractListModel(parent)
{
}

void ConsolesModel::addConsole(const Console &v_console)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _consoles << v_console;
    endInsertRows();
}

int ConsolesModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return _consoles.count();
}

QVariant ConsolesModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= _consoles.count())
        return QVariant();

    const Console &console = _consoles[index.row()];
    if (role == NameField)
        return console.name();
    else if (role == ChannelField)
        return console.channel();
    return QVariant();
}

bool ConsolesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Console &console = _consoles[index.row()];

    if (role == NameField)
        console.setName(value.toString());
    else if (role == ChannelField)
        console.setChannel(value.toInt());

    return true;
}

bool ConsolesModel::setProperty(int row, QString propertyName, QVariant propertyValue)
{
    return setData(this->index(row), propertyValue, field_roles.find(propertyName.toStdString().c_str()).value());
}

QHash<int, QByteArray> ConsolesModel::roleNames() const
{
    return role_fields;
}
