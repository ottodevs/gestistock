/****************************************************************************
** Meta object code from reading C++ file 'qcalendarwidgetnew.h'
**
** Created: Wed 15. Aug 18:24:14 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../qcalendarwidgetnew.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcalendarwidgetnew.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCalendarWidgetNew[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       1,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
      26,   19, 0x43095103,

       0        // eod
};

static const char qt_meta_stringdata_QCalendarWidgetNew[] = {
    "QCalendarWidgetNew\0QColor\0color\0"
};

const QMetaObject QCalendarWidgetNew::staticMetaObject = {
    { &QCalendarWidget::staticMetaObject, qt_meta_stringdata_QCalendarWidgetNew,
      qt_meta_data_QCalendarWidgetNew, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCalendarWidgetNew::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCalendarWidgetNew::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCalendarWidgetNew::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCalendarWidgetNew))
        return static_cast<void*>(const_cast< QCalendarWidgetNew*>(this));
    return QCalendarWidget::qt_metacast(_clname);
}

int QCalendarWidgetNew::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCalendarWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = getColor(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setColor(*reinterpret_cast< QColor*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
