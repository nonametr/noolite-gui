#ifndef CHANNELACTIONSMODEL_H
#define CHANNELACTIONSMODEL_H

#include "qobject.h"

class ChannelAction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString script READ scriptRead WRITE setScript NOTIFY scriptChanged)
    Q_PROPERTY(qint32 action READ actionRead WRITE setAction NOTIFY actionChanged)

public:
    ChannelAction(qint32 new_action, QString new_script) : _action(new_action), _script(new_script)
    {}
    ChannelAction() = default;
    virtual ~ChannelAction() override = default;

    ChannelAction(const ChannelAction &action)
    {
        this->_action = action.actionRead();
        this->_script = action.scriptRead();
    }

    ChannelAction & operator = (const ChannelAction &action)
    {
        this->_action = action.actionRead();
        this->_script = action.scriptRead();
    }

    QString scriptRead() const;
    qint32 actionRead() const;

    void setScript(QString new_script);
    void setAction(qint32 new_action);

signals:
    void scriptChanged();
    void actionChanged();

private:
    qint32 _action;
    QString _script;
};

class ChannelActions : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qint32 channel_id READ channelRead() WRITE setChannelId NOTIFY channelIdChanged)
    Q_PROPERTY(QList<ChannelAction> actions READ actionsRead WRITE setActions NOTIFY actionsChanged)

public:
    ChannelActions(const ChannelActions &actions)
    {
        this->_channel_id = actions.channelRead();
        this->_actions = actions.actionsRead();
    }

    ChannelActions & operator = (const ChannelActions &actions)
    {
        this->_channel_id = actions.channelRead();
        this->_actions = actions.actionsRead();
    }

    ChannelActions() = default;
    virtual ~ChannelActions() override = default;

    qint32 channelRead() const;
    QList<ChannelAction> actionsRead() const;

    void setChannelId(qint32 new_channel_id);
    void setActions(QList<ChannelAction> new_actions);

signals:
    void channelIdChanged();
    void actionsChanged();

private:
    qint32 _channel_id;
    QList<ChannelAction> _actions;
};

#endif // CHANNELACTIONSMODEL_H
