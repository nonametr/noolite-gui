#include "rx_gui_model.h"

int RxGUIModel::rxHeightRead() const
{
    return rxHeight;
}

int RxGUIModel::rxWidthRead() const
{
    return rxWidth;
}

int RxGUIModel::rxXRead() const
{
    return rxX;
}

int RxGUIModel::rxYRead() const
{
    return rxY;
}

void RxGUIModel::rxWidthWrite(int value)
{
    rxWidth = value;

    emit rxWidthChanged();
}

void RxGUIModel::rxHeightWrite(int value)
{
    rxHeight = value;

    emit rxHeightChanged();
}

void RxGUIModel::rxYWrite(int value)
{
    rxY = value;

    emit rxYChanged();
}

void RxGUIModel::rxXWrite(int value)
{
    rxX = value;

    emit rxXChanged();
}
