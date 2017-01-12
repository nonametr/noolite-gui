#include "tx_gui_model.h"

TxGUIModel::TxGUIModel()
{}

int TxGUIModel::txHeightRead() const
{
    return txHeight;
}

int TxGUIModel::txWidthRead() const
{
    return txWidth;
}

int TxGUIModel::txXRead() const
{
    return txX;
}

int TxGUIModel::txYRead() const
{
    return txY;
}

void TxGUIModel::txHeightWrite(int value)
{
    txHeight = value;

    emit txHeightChanged();
}

void TxGUIModel::txWidthWrite(int value)
{
    txWidth = value;

    emit txWidthChanged();
}

void TxGUIModel::txXWrite(int value)
{
    txX = value;

    emit txXChanged();
}

void TxGUIModel::txYWrite(int value)
{
    txY = value;

    emit txYChanged();
}
