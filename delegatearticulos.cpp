#include "delegatearticulos.h"

DelegateArticulos::DelegateArticulos(QObject *parent):QItemDelegate(parent){}

void DelegateArticulos::paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QSqlQuery query;

    query.exec("SELECT stockminimo FROM articulos WHERE articulos.codigoean = '"+index.sibling(index.row(),0).data().toString()+"' ");
    query.first();

    if(index.sibling(index.row(),2).data().toInt() < query.value(0).toInt())
        painter->fillRect(option.rect, Qt::yellow);


    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    QStyleOptionViewItem myOption = option;

    myOption.displayAlignment = Qt::AlignHCenter | Qt::AlignVCenter;

    drawDisplay(painter, myOption, myOption.rect,text);
    drawFocus(painter, myOption, myOption.rect);
}


