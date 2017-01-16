#ifndef RX_CONSOLESMODEL_H
#define RX_CONSOLESMODEL_H

#include <QAbstractListModel>
#include "rx_channel_cfg_model.h"

class RxChannel
{
public:
    RxChannel(const QString &v_name, const qint32 &v_channel, QList<RxChannelCfgModel> &v_channelActions);

    QString name() const;
    qint32 channel() const;
    QList<RxChannelCfgModel> &channelActions();

    void setName(const QString &v_name);
    void setChannel(const qint32 &v_channel);
    void setChannelActions(const QList<RxChannelCfgModel> &v_channelActions);

private:
    QString _name;
    qint32 _channel;
    QList<RxChannelCfgModel> _channelActions;
};

class RxChannelsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemFields {
        NameField = Qt::UserRole + 1,
        ChannelField
    };

    RxChannelsModel(QObject *parent = 0);

    RxChannelsModel(const RxChannelsModel &r) : QAbstractListModel(this)
    {
        this->_channels = r._channels;
    }

    RxChannelsModel & operator = (const RxChannelsModel &r)
    {
        this->_channels = r._channels;

        return *this;
    }

    void addChannel(const RxChannel &v_console);
    QList<RxChannel> &getChannels(){ return _channels; }

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

protected:
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    bool setProperty(int row, QString propertyName, QVariant propertyValue);

private:
    QList<RxChannel> _channels;

    static QHash<int, QByteArray> role_fields;
    static QHash<QByteArray, int> field_roles;
};

#endif // RX_CONSOLESMODEL_H
