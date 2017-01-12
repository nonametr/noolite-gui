#ifndef TX_GUI_MODEL_H
#define TX_GUI_MODEL_H

#include <QObject>

class TxGUIModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int txX READ txXRead WRITE txXWrite NOTIFY txXChanged)
    Q_PROPERTY(int txY READ txYRead WRITE txYWrite NOTIFY txYChanged)
    Q_PROPERTY(int txHeight READ txHeightRead WRITE txHeightWrite NOTIFY txHeightChanged)
    Q_PROPERTY(int txWidth READ txWidthRead WRITE txWidthWrite NOTIFY txWidthChanged)

public:
    TxGUIModel();
    TxGUIModel(const TxGUIModel &r)
    {
        txX = r.txX;
        txY = r.txY;
        txHeight = r.txHeight;
        txWidth = r.txWidth;
    }

    TxGUIModel & operator = (const TxGUIModel &r)
    {
        txX = r.txX;
        txY = r.txY;
        txHeight = r.txHeight;
        txWidth = r.txWidth;

        return *this;
    }

    int txXRead() const;
    int txYRead() const;
    int txHeightRead() const;
    int txWidthRead() const;


    void txXWrite(int value);
    void txYWrite(int value);
    void txHeightWrite(int value);
    void txWidthWrite(int value);

signals:
    void txXChanged();
    void txYChanged();
    void txHeightChanged();
    void txWidthChanged();

private:
    int txX;
    int txY;
    int txHeight;
    int txWidth;
};

#endif // TX_GUI_MODEL_H
