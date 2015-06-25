#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

class DataObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ name WRITE setName NOTIFY nameChanged)

public:
    DataObject(QString v_name) : _name(v_name) {}
    virtual ~DataObject() override = default;

    QString name();
    void setName(const QString &v_name);

signals:
    void nameChanged();

private:
    QString _name;
};


#endif // DATAOBJECT_H
