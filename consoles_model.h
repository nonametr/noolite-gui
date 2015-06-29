#ifndef CONSOLESMODEL_H
#define CONSOLESMODEL_H

#include <QAbstractListModel>

class Console
{
public:
    Console(const QString &v_name, const qint32 &v_channel);

    QString name() const;
    qint32 channel() const;

    void setName(const QString &v_name);
    void setChannel(const qint32 &v_channel);

private:
    QString _name;
    qint32 _channel;
};

class ConsolesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemFields {
        NameField = Qt::UserRole + 1,
        ChannelField
    };

    ConsolesModel(QObject *parent = 0);

    void addConsole(const Console &v_console);

    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

protected:
    virtual QHash<int, QByteArray> roleNames() const override;

public slots:
    bool setProperty(int row, QString propertyName, QVariant propertyValue);

private:
    QList<Console> _consoles;

    static QHash<int, QByteArray> role_fields;
    static QHash<QByteArray, int> field_roles;
};

#endif // CONSOLESMODEL_H
