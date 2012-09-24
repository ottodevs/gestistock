#include "qsqlqueryconexiones.h"


void QSqlQueryConexiones::refrescar(QString cn)
{
    //Colocamos la consulta
    setQuery(cn);
}

