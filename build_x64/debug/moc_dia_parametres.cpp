/****************************************************************************
** Meta object code from reading C++ file 'dia_parametres.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Minecraft_Advancements/settings/dia_parametres.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dia_parametres.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DIA_Parametres_t {
    QByteArrayData data[12];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DIA_Parametres_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DIA_Parametres_t qt_meta_stringdata_DIA_Parametres = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DIA_Parametres"
QT_MOC_LITERAL(1, 15, 14), // "setRestorePath"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "state"
QT_MOC_LITERAL(4, 37, 17), // "setRestoreSizePos"
QT_MOC_LITERAL(5, 55, 31), // "setMessageConfirmationFermeture"
QT_MOC_LITERAL(6, 87, 16), // "setMiseAJourAuto"
QT_MOC_LITERAL(7, 104, 7), // "enabled"
QT_MOC_LITERAL(8, 112, 22), // "setNombreJourMiseAJour"
QT_MOC_LITERAL(9, 135, 10), // "nombreJour"
QT_MOC_LITERAL(10, 146, 16), // "setMiseAJourBeta"
QT_MOC_LITERAL(11, 163, 7) // "checked"

    },
    "DIA_Parametres\0setRestorePath\0\0state\0"
    "setRestoreSizePos\0setMessageConfirmationFermeture\0"
    "setMiseAJourAuto\0enabled\0"
    "setNombreJourMiseAJour\0nombreJour\0"
    "setMiseAJourBeta\0checked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DIA_Parametres[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    1,   47,    2, 0x08 /* Private */,
       5,    1,   50,    2, 0x08 /* Private */,
       6,    1,   53,    2, 0x08 /* Private */,
       8,    1,   56,    2, 0x08 /* Private */,
      10,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Bool,   11,

       0        // eod
};

void DIA_Parametres::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DIA_Parametres *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setRestorePath((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setRestoreSizePos((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setMessageConfirmationFermeture((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setMiseAJourAuto((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setNombreJourMiseAJour((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setMiseAJourBeta((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DIA_Parametres::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_DIA_Parametres.data,
    qt_meta_data_DIA_Parametres,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DIA_Parametres::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DIA_Parametres::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DIA_Parametres.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DIA_Parametres::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
