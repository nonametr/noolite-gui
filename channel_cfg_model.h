#ifndef CHANNELACTIONSMODEL_H
#define CHANNELACTIONSMODEL_H

#include "qobject.h"

class ChannelCfgModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString script READ scriptRead WRITE setScript NOTIFY scriptChanged)
    Q_PROPERTY(bool fw READ fwRead WRITE setFw NOTIFY fwChanged)
    Q_PROPERTY(bool fwExt READ fwExtRead WRITE setFwExt NOTIFY fwExtChanged)

public:
    ChannelCfgModel(QString new_script, bool new_fw, bool new_fw_ext) : _script(new_script), _fw(new_fw), _fwExt(new_fw_ext) {}
    ChannelCfgModel() = default;
    virtual ~ChannelCfgModel() override = default;

    ChannelCfgModel(const ChannelCfgModel &r)
    {
        this->_script = r.scriptRead();
        this->_fw = r.fwRead();
        this->_fwExt = r.fwExtRead();
    }

    ChannelCfgModel & operator = (const ChannelCfgModel &r)
    {
        this->_script = r.scriptRead();
        this->_fw = r.fwRead();
        this->_fwExt = r.fwExtRead();

        return *this;
    }

    QString scriptRead() const;
    bool fwRead() const;
    bool fwExtRead() const;

    void setScript(QString new_script);
    void setFw(bool new_fw);
    void setFwExt(bool new_fwExt);

signals:
    void scriptChanged();
    void fwChanged();
    void fwExtChanged();

private:
    QString _script = "";
    bool _fw = false;
    bool _fwExt = false;
};

#endif // CHANNELACTIONSMODEL_H