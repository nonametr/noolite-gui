#ifndef RX_GUI_MODEL_H
#define RX_GUI_MODEL_H

#include <QObject>

class RxGUIModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int rxX READ rxXRead WRITE rxXWrite NOTIFY rxXChanged)
    Q_PROPERTY(int rxY READ rxYRead WRITE rxYWrite NOTIFY rxYChanged)
    Q_PROPERTY(int rxHeight READ rxHeightRead WRITE rxHeightWrite NOTIFY rxHeightChanged)
    Q_PROPERTY(int rxWidth READ rxWidthRead WRITE rxWidthWrite NOTIFY rxWidthChanged)

public:
    RxGUIModel()  : QObject(nullptr) {}
    RxGUIModel(const RxGUIModel &r) : QObject(nullptr)
    {
        rxX = r.rxX;
        rxY = r.rxY;
        rxHeight = r.rxHeight;
        rxWidth = r.rxWidth;
    }

    RxGUIModel & operator = (const RxGUIModel &r)
    {
        rxX = r.rxX;
        rxY = r.rxY;
        rxHeight = r.rxHeight;
        rxWidth = r.rxWidth;

        return *this;
    }

    int rxXRead() const;
    int rxYRead() const;
    int rxHeightRead() const;
    int rxWidthRead() const;

    void rxYWrite(int value);
    void rxXWrite(int value);
    void rxWidthWrite(int value);
    void rxHeightWrite(int value);

signals:
    void rxXChanged();
    void rxYChanged();
    void rxHeightChanged();
    void rxWidthChanged();

private:
    int rxX;
    int rxY;
    int rxHeight;
    int rxWidth;
};

#endif // RX_GUI_MODEL_H
