#include "data_object.h"

QString DataObject::name()
{
    return _name;
}

void DataObject::setName(const QString &v_name)
{
    _name = v_name;
    emit nameChanged();
}
