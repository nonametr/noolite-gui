#ifndef TX_CONSOLESMODEL_H
#define TX_CONSOLESMODEL_H

#include <QAbstractListModel>

class TxChannel
{
public:
    TxChannel(const QString &v_name, const qint32 &v_channel);

    QString name() const;
    qint32 channel() const;

    void setName(const QString &v_name);
    void setChannel(const qint32 &v_channel);

private:
    QString _name;
    qint32 _channel;
};

class TxChannelsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemFields {
        NameField = Qt::UserRole + 1,
        ChannelField
    };

    TxChannelsModel(QObject *parent = 0);

    TxChannelsModel(const TxChannelsModel &r) : QAbstractListModel(this)
    {
        this->_channels = r._channels;
    }

    TxChannelsModel & operator = (const TxChannelsModel &r)
    {
        this->_channels = r._channels;

        return *this;
    }

    void addChannel(const TxChannel &v_console);
    QList<TxChannel> &getChannels(){ return _channels; }

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

protected:
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    bool setProperty(int row, QString propertyName, QVariant propertyValue);

private:
    QList<TxChannel> _channels;

    static QHash<int, QByteArray> role_fields;
    static QHash<QByteArray, int> field_roles;
};

#endif // TX_CONSOLESMODEL_H
