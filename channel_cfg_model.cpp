#include "channel_cfg_model.h"
#include <QDebug>

QString ChannelCfgModel::scriptRead() const
{
    return _script;
}

void ChannelCfgModel::setScript(QString new_script)
{
    if(_script == new_script) return;

    _script = new_script;

    emit scriptChanged();
}

bool ChannelCfgModel::fwRead() const
{
    return _fw;
}

bool ChannelCfgModel::fwExtRead() const
{
    return _fwExt;
}

void ChannelCfgModel::setFw(bool new_fw)
{
    if(_fw == new_fw) return;

    _fw = new_fw;
    emit fwChanged();
}

void ChannelCfgModel::setFwExt(bool new_fwExt)
{
    if(_fwExt == new_fwExt) return;

    _fwExt = new_fwExt;
    emit fwExtChanged();
}
