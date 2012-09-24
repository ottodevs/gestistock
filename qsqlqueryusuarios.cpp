#include "qsqlqueryusuarios.h"

void QSqlQueryUsuarios::refrescar(QString cn)
{
    //Colocamos la consulta
    setQuery(cn);
}
