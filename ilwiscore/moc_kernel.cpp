/****************************************************************************
** Meta object code from reading C++ file 'kernel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/kernel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kernel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ilwis__Kernel_t {
    QByteArrayData data[23];
    char stringdata0[250];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ilwis__Kernel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ilwis__Kernel_t qt_meta_stringdata_Ilwis__Kernel = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Ilwis::Kernel"
QT_MOC_LITERAL(1, 14, 9), // "doCommand"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "expr"
QT_MOC_LITERAL(4, 30, 17), // "ExecutionContext*"
QT_MOC_LITERAL(5, 48, 3), // "ctx"
QT_MOC_LITERAL(6, 52, 18), // "updateTranquilizer"
QT_MOC_LITERAL(7, 71, 2), // "id"
QT_MOC_LITERAL(8, 74, 6), // "amount"
QT_MOC_LITERAL(9, 81, 18), // "createTranquilizer"
QT_MOC_LITERAL(10, 100, 5), // "title"
QT_MOC_LITERAL(11, 106, 11), // "description"
QT_MOC_LITERAL(12, 118, 5), // "start"
QT_MOC_LITERAL(13, 124, 3), // "end"
QT_MOC_LITERAL(14, 128, 18), // "removeTranquilizer"
QT_MOC_LITERAL(15, 147, 14), // "stopAllThreads"
QT_MOC_LITERAL(16, 162, 11), // "sendMessage"
QT_MOC_LITERAL(17, 174, 4), // "type"
QT_MOC_LITERAL(18, 179, 7), // "subtype"
QT_MOC_LITERAL(19, 187, 10), // "parameters"
QT_MOC_LITERAL(20, 198, 18), // "changeTranquilizer"
QT_MOC_LITERAL(21, 217, 18), // "deleteTranquilizer"
QT_MOC_LITERAL(22, 236, 13) // "acceptMessage"

    },
    "Ilwis::Kernel\0doCommand\0\0expr\0"
    "ExecutionContext*\0ctx\0updateTranquilizer\0"
    "id\0amount\0createTranquilizer\0title\0"
    "description\0start\0end\0removeTranquilizer\0"
    "stopAllThreads\0sendMessage\0type\0subtype\0"
    "parameters\0changeTranquilizer\0"
    "deleteTranquilizer\0acceptMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ilwis__Kernel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       6,    2,   64,    2, 0x06 /* Public */,
       9,    5,   69,    2, 0x06 /* Public */,
      14,    1,   80,    2, 0x06 /* Public */,
      15,    0,   83,    2, 0x06 /* Public */,
      16,    3,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    2,   91,    2, 0x0a /* Public */,
      21,    1,   96,    2, 0x0a /* Public */,
      22,    3,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Double,    7,    8,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QString, QMetaType::QString, QMetaType::Double, QMetaType::Double,    7,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::ULongLong,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QVariantMap,   17,   18,   19,

 // slots: parameters
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Double,    7,    8,
    QMetaType::Void, QMetaType::ULongLong,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QVariantMap,   17,   18,   19,

       0        // eod
};

void Ilwis::Kernel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Kernel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->doCommand((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< ExecutionContext*(*)>(_a[2]))); break;
        case 1: _t->updateTranquilizer((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->createTranquilizer((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 3: _t->removeTranquilizer((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 4: _t->stopAllThreads(); break;
        case 5: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QVariantMap(*)>(_a[3]))); break;
        case 6: _t->changeTranquilizer((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 7: _t->deleteTranquilizer((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 8: _t->acceptMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QVariantMap(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Kernel::*)(const QString & , ExecutionContext * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::doCommand)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(quint64 , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::updateTranquilizer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(quint64 , const QString & , const QString & , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::createTranquilizer)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::removeTranquilizer)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Kernel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::stopAllThreads)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Kernel::*)(const QString & , const QString & , const QVariantMap & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Kernel::sendMessage)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Ilwis::Kernel::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Ilwis__Kernel.data,
    qt_meta_data_Ilwis__Kernel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ilwis::Kernel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ilwis::Kernel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ilwis__Kernel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Ilwis::Kernel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Ilwis::Kernel::doCommand(const QString & _t1, ExecutionContext * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Ilwis::Kernel::updateTranquilizer(quint64 _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Ilwis::Kernel::createTranquilizer(quint64 _t1, const QString & _t2, const QString & _t3, double _t4, double _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Ilwis::Kernel::removeTranquilizer(quint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Ilwis::Kernel::stopAllThreads()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Ilwis::Kernel::sendMessage(const QString & _t1, const QString & _t2, const QVariantMap & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
