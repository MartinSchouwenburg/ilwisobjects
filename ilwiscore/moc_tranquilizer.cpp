/****************************************************************************
** Meta object code from reading C++ file 'tranquilizer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/util/tranquilizer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tranquilizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ilwis__TranquilizerWorker_t {
    QByteArrayData data[14];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ilwis__TranquilizerWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ilwis__TranquilizerWorker_t qt_meta_stringdata_Ilwis__TranquilizerWorker = {
    {
QT_MOC_LITERAL(0, 0, 25), // "Ilwis::TranquilizerWorker"
QT_MOC_LITERAL(1, 26, 22), // "sendUpdateTranquilizer"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 2), // "id"
QT_MOC_LITERAL(4, 53, 6), // "amount"
QT_MOC_LITERAL(5, 60, 22), // "sendCreateTranquilizer"
QT_MOC_LITERAL(6, 83, 5), // "title"
QT_MOC_LITERAL(7, 89, 11), // "description"
QT_MOC_LITERAL(8, 101, 5), // "start"
QT_MOC_LITERAL(9, 107, 3), // "end"
QT_MOC_LITERAL(10, 111, 22), // "sendRemoveTranquilizer"
QT_MOC_LITERAL(11, 134, 18), // "updateTranquilizer"
QT_MOC_LITERAL(12, 153, 18), // "createTranquilizer"
QT_MOC_LITERAL(13, 172, 18) // "removeTranquilizer"

    },
    "Ilwis::TranquilizerWorker\0"
    "sendUpdateTranquilizer\0\0id\0amount\0"
    "sendCreateTranquilizer\0title\0description\0"
    "start\0end\0sendRemoveTranquilizer\0"
    "updateTranquilizer\0createTranquilizer\0"
    "removeTranquilizer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ilwis__TranquilizerWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       5,    5,   49,    2, 0x06 /* Public */,
      10,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   63,    2, 0x0a /* Public */,
      12,    5,   68,    2, 0x0a /* Public */,
      13,    1,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QString, QMetaType::QString, QMetaType::Double, QMetaType::Double,    3,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::ULongLong,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QString, QMetaType::QString, QMetaType::Double, QMetaType::Double,    3,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::ULongLong,    3,

       0        // eod
};

void Ilwis::TranquilizerWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TranquilizerWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendUpdateTranquilizer((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->sendCreateTranquilizer((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 2: _t->sendRemoveTranquilizer((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 3: _t->updateTranquilizer((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 4: _t->createTranquilizer((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 5: _t->removeTranquilizer((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TranquilizerWorker::*)(quint64 , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TranquilizerWorker::sendUpdateTranquilizer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TranquilizerWorker::*)(quint64 , const QString & , const QString & , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TranquilizerWorker::sendCreateTranquilizer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TranquilizerWorker::*)(quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TranquilizerWorker::sendRemoveTranquilizer)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Ilwis::TranquilizerWorker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Ilwis__TranquilizerWorker.data,
    qt_meta_data_Ilwis__TranquilizerWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ilwis::TranquilizerWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ilwis::TranquilizerWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ilwis__TranquilizerWorker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Ilwis::TranquilizerWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Ilwis::TranquilizerWorker::sendUpdateTranquilizer(quint64 _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Ilwis::TranquilizerWorker::sendCreateTranquilizer(quint64 _t1, const QString & _t2, const QString & _t3, double _t4, double _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Ilwis::TranquilizerWorker::sendRemoveTranquilizer(quint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_Ilwis__BaseTranquilizer_t {
    QByteArrayData data[11];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ilwis__BaseTranquilizer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ilwis__BaseTranquilizer_t qt_meta_stringdata_Ilwis__BaseTranquilizer = {
    {
QT_MOC_LITERAL(0, 0, 23), // "Ilwis::BaseTranquilizer"
QT_MOC_LITERAL(1, 24, 18), // "updateTranquilizer"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 2), // "id"
QT_MOC_LITERAL(4, 47, 7), // "current"
QT_MOC_LITERAL(5, 55, 18), // "removeTranquilizer"
QT_MOC_LITERAL(6, 74, 19), // "tranquilizerCreated"
QT_MOC_LITERAL(7, 94, 5), // "title"
QT_MOC_LITERAL(8, 100, 11), // "description"
QT_MOC_LITERAL(9, 112, 3), // "end"
QT_MOC_LITERAL(10, 116, 16) // "stopTranquilizer"

    },
    "Ilwis::BaseTranquilizer\0updateTranquilizer\0"
    "\0id\0current\0removeTranquilizer\0"
    "tranquilizerCreated\0title\0description\0"
    "end\0stopTranquilizer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ilwis__BaseTranquilizer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    1,   39,    2, 0x06 /* Public */,
       6,    4,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::ULongLong,    3,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::QString, QMetaType::QString, QMetaType::ULongLong,    3,    7,    8,    9,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Ilwis::BaseTranquilizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BaseTranquilizer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateTranquilizer((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->removeTranquilizer((*reinterpret_cast< quint64(*)>(_a[1]))); break;
        case 2: _t->tranquilizerCreated((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< quint64(*)>(_a[4]))); break;
        case 3: _t->stopTranquilizer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BaseTranquilizer::*)(quint64 , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseTranquilizer::updateTranquilizer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BaseTranquilizer::*)(quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseTranquilizer::removeTranquilizer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BaseTranquilizer::*)(quint64 , const QString & , const QString & , quint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BaseTranquilizer::tranquilizerCreated)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Ilwis::BaseTranquilizer::staticMetaObject = { {
    &Tranquilizer::staticMetaObject,
    qt_meta_stringdata_Ilwis__BaseTranquilizer.data,
    qt_meta_data_Ilwis__BaseTranquilizer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ilwis::BaseTranquilizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ilwis::BaseTranquilizer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ilwis__BaseTranquilizer.stringdata0))
        return static_cast<void*>(this);
    return Tranquilizer::qt_metacast(_clname);
}

int Ilwis::BaseTranquilizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Tranquilizer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Ilwis::BaseTranquilizer::updateTranquilizer(quint64 _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Ilwis::BaseTranquilizer::removeTranquilizer(quint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Ilwis::BaseTranquilizer::tranquilizerCreated(quint64 _t1, const QString & _t2, const QString & _t3, quint64 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_Ilwis__EmptyTranquilizer_t {
    QByteArrayData data[1];
    char stringdata0[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ilwis__EmptyTranquilizer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ilwis__EmptyTranquilizer_t qt_meta_stringdata_Ilwis__EmptyTranquilizer = {
    {
QT_MOC_LITERAL(0, 0, 24) // "Ilwis::EmptyTranquilizer"

    },
    "Ilwis::EmptyTranquilizer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ilwis__EmptyTranquilizer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Ilwis::EmptyTranquilizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Ilwis::EmptyTranquilizer::staticMetaObject = { {
    &BaseTranquilizer::staticMetaObject,
    qt_meta_stringdata_Ilwis__EmptyTranquilizer.data,
    qt_meta_data_Ilwis__EmptyTranquilizer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ilwis::EmptyTranquilizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ilwis::EmptyTranquilizer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ilwis__EmptyTranquilizer.stringdata0))
        return static_cast<void*>(this);
    return BaseTranquilizer::qt_metacast(_clname);
}

int Ilwis::EmptyTranquilizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseTranquilizer::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
