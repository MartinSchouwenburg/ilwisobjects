/****************************************************************************
** Meta object code from reading C++ file 'pythonapi_qissuelogger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/pythonapi_qissuelogger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pythonapi_qissuelogger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_pythonapi__QIssueLogger_t {
    QByteArrayData data[5];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pythonapi__QIssueLogger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pythonapi__QIssueLogger_t qt_meta_stringdata_pythonapi__QIssueLogger = {
    {
QT_MOC_LITERAL(0, 0, 23), // "pythonapi::QIssueLogger"
QT_MOC_LITERAL(1, 24, 17), // "ilwiserrormessage"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 18), // "Ilwis::IssueObject"
QT_MOC_LITERAL(4, 62, 11) // "issueObject"

    },
    "pythonapi::QIssueLogger\0ilwiserrormessage\0"
    "\0Ilwis::IssueObject\0issueObject"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pythonapi__QIssueLogger[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void pythonapi::QIssueLogger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QIssueLogger *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ilwiserrormessage((*reinterpret_cast< const Ilwis::IssueObject(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Ilwis::IssueObject >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject pythonapi::QIssueLogger::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_pythonapi__QIssueLogger.data,
    qt_meta_data_pythonapi__QIssueLogger,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *pythonapi::QIssueLogger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pythonapi::QIssueLogger::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_pythonapi__QIssueLogger.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int pythonapi::QIssueLogger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
