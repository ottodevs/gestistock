#include "qsqlquerysalidas.h"

void QSqlQuerySalidas::refrescar(QString cn)
{
    //Colocamos la consulta
    setQuery(cn);
}
