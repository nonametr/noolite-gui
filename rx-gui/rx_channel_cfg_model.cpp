#include "rx_channel_cfg_model.h"
#include <QDebug>

QString RxChannelCfgModel::scriptRead() const
{
    return _script;
}

void RxChannelCfgModel::setScript(QString new_script)
{
    if(_script == new_script) return;

    _script = new_script;

    emit scriptChanged();
}

bool RxChannelCfgModel::fwRead() const
{
    return _fw;
}

bool RxChannelCfgModel::fwExtRead() const
{
    return _fwExt;
}

void RxChannelCfgModel::setFw(bool new_fw)
{
    if(_fw == new_fw) return;

    _fw = new_fw;
    emit fwChanged();
}

void RxChannelCfgModel::setFwExt(bool new_fwExt)
{
    if(_fwExt == new_fwExt) return;

    _fwExt = new_fwExt;
    emit fwExtChanged();
}
