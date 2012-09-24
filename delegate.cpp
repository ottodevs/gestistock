#include "delegate.h"

Delegate::Delegate(QObject *parent):QItemDelegate(parent){}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{   
    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    QStyleOptionViewItem myOption = option;

    myOption.displayAlignment = Qt::AlignHCenter | Qt::AlignVCenter;

    drawDisplay(painter, myOption, myOption.rect,text);
    drawFocus(painter, myOption, myOption.rect);

}






