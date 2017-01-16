#ifndef CHANNELACTIONSMODEL_H
#define CHANNELACTIONSMODEL_H

#include "qobject.h"

class RxChannelCfgModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString script READ scriptRead WRITE setScript NOTIFY scriptChanged)
    Q_PROPERTY(bool fw READ fwRead WRITE setFw NOTIFY fwChanged)
    Q_PROPERTY(bool fwExt READ fwExtRead WRITE setFwExt NOTIFY fwExtChanged)

public:
    RxChannelCfgModel(QString new_script, bool new_fw, bool new_fw_ext) : QObject(nullptr), _script(new_script), _fw(new_fw), _fwExt(new_fw_ext) {}
    RxChannelCfgModel() : QObject(nullptr) {}
    virtual ~RxChannelCfgModel() override = default;

    RxChannelCfgModel(const RxChannelCfgModel &r) : QObject(nullptr)
    {
        this->_script = r.scriptRead();
        this->_fw = r.fwRead();
        this->_fwExt = r.fwExtRead();
    }

    RxChannelCfgModel & operator = (const RxChannelCfgModel &r)
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
