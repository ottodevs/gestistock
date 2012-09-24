#include "qsqlqueryarticulosproveedor.h"


void QSqlQueryArticulosProveedor::refrescar(QString consulta)
{
    setQuery(consulta);
}

void QSqlQueryArticulosProveedor::refrescarPrecioDesc()
{
    //Rellenamos el tableView
    setQuery("select CodigoEAN, Descripcion, Cantidad, IVA from articulos ORDER BY  Cantidad desc ");
}

void QSqlQueryArticulosProveedor::refrescarPrecioAsc()
{
    setQuery("select CodigoEAN, Descripcion, Cantidad, IVA from articulos ORDER BY  Cantidad asc ");
}


void QSqlQueryArticulosProveedor::refrescarDescripcionDesc()
{
    //Rellenamos el tableView
    setQuery("select CodigoEAN, Descripcion, Cantidad, IVA from articulos ORDER BY  Descripcion desc ");
}

void QSqlQueryArticulosProveedor::refrescarDescripcionAsc()
{
    setQuery("select CodigoEAN, Descripcion, Cantidad, IVA from articulos ORDER BY  Descripcion asc ");
}


void QSqlQueryArticulosProveedor::refrescarCodigoEANDesc()
{
    //Rellenamos el tableView
    setQuery("select CodigoEAN, Descripcion, Cantidad, IVA from articulos ORDER BY  CodigoEAN desc ");
}


void QSqlQueryArticulosProveedor::refrescarCodigoEANAsc()
{
    setQuery("select CodigoEAN, Descripcion, Cantidad, IVA from articulos ORDER BY  CodigoEAN asc ");
}

