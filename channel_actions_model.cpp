#include "channel_actions_model.h"

QString ChannelAction::scriptRead() const
{
    return _script;
}

qint32 ChannelAction::actionRead() const
{
    return _action;
}

void ChannelAction::setScript(QString new_script)
{
    _script = new_script;
}

void ChannelAction::setAction(qint32 new_action)
{
    _action = new_action;
}

qint32 ChannelActions::channelRead() const
{
    return _channel_id;
}

//-------------------------------------

QList<ChannelAction> ChannelActions::actionsRead() const
{
    return _actions;
}

void ChannelActions::setChannelId(qint32 new_channel_id)
{
    _channel_id = new_channel_id;
}

void ChannelActions::setActions(QList<ChannelAction> new_actions)
{
    _actions = new_actions;
}
