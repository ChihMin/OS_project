/****************************************************************************
** Meta object code from reading C++ file 'miku.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "miku.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'miku.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Miku[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,   15,   15,   15, 0x05,
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Miku[] = {
    "Miku\0clicked()\0\0timeout()\0setPosition()\0"
};

void Miku::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Miku *_t = static_cast<Miku *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->timeout(); break;
        case 2: _t->setPosition(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Miku::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Miku::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Miku,
      qt_meta_data_Miku, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Miku::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Miku::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Miku::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Miku))
        return static_cast<void*>(const_cast< Miku*>(this));
    return QWidget::qt_metacast(_clname);
}

int Miku::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Miku::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Miku::timeout()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
