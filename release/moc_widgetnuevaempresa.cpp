/****************************************************************************
** Meta object code from reading C++ file 'widgetnuevaempresa.h'
**
** Created: Fri 20. Jul 18:32:22 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widgetnuevaempresa.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgetnuevaempresa.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WidgetNuevaEmpresa[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,
      41,   19,   19,   19, 0x08,
      64,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WidgetNuevaEmpresa[] = {
    "WidgetNuevaEmpresa\0\0on_pbSalir_clicked()\0"
    "on_pbLimpiar_clicked()\0on_pbCompletar_clicked()\0"
};

const QMetaObject WidgetNuevaEmpresa::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WidgetNuevaEmpresa,
      qt_meta_data_WidgetNuevaEmpresa, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WidgetNuevaEmpresa::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WidgetNuevaEmpresa::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WidgetNuevaEmpresa::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetNuevaEmpresa))
        return static_cast<void*>(const_cast< WidgetNuevaEmpresa*>(this));
    return QWidget::qt_metacast(_clname);
}

int WidgetNuevaEmpresa::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pbSalir_clicked(); break;
        case 1: on_pbLimpiar_clicked(); break;
        case 2: on_pbCompletar_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
