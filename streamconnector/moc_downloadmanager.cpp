/****************************************************************************
** Meta object code from reading C++ file 'downloadmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/downloadmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downloadmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ilwis__Stream__DownloadManager_t {
    QByteArrayData data[13];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ilwis__Stream__DownloadManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ilwis__Stream__DownloadManager_t qt_meta_stringdata_Ilwis__Stream__DownloadManager = {
    {
QT_MOC_LITERAL(0, 0, 30), // "Ilwis::Stream::DownloadManager"
QT_MOC_LITERAL(1, 31, 9), // "readReady"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 15), // "readReadyRaster"
QT_MOC_LITERAL(4, 58, 16), // "downloadProgress"
QT_MOC_LITERAL(5, 75, 13), // "bytesReceived"
QT_MOC_LITERAL(6, 89, 10), // "bytesTotal"
QT_MOC_LITERAL(7, 100, 5), // "error"
QT_MOC_LITERAL(8, 106, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(9, 134, 4), // "code"
QT_MOC_LITERAL(10, 139, 16), // "finishedMetadata"
QT_MOC_LITERAL(11, 156, 12), // "finishedData"
QT_MOC_LITERAL(12, 169, 20) // "finishedDataExplorer"

    },
    "Ilwis::Stream::DownloadManager\0readReady\0"
    "\0readReadyRaster\0downloadProgress\0"
    "bytesReceived\0bytesTotal\0error\0"
    "QNetworkReply::NetworkError\0code\0"
    "finishedMetadata\0finishedData\0"
    "finishedDataExplorer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ilwis__Stream__DownloadManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x09 /* Protected */,
       3,    0,   50,    2, 0x09 /* Protected */,
       4,    2,   51,    2, 0x09 /* Protected */,
       7,    1,   56,    2, 0x09 /* Protected */,
      10,    0,   59,    2, 0x09 /* Protected */,
      11,    0,   60,    2, 0x09 /* Protected */,
      12,    0,   61,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Ilwis::Stream::DownloadManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DownloadManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readReady(); break;
        case 1: _t->readReadyRaster(); break;
        case 2: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->error((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 4: _t->finishedMetadata(); break;
        case 5: _t->finishedData(); break;
        case 6: _t->finishedDataExplorer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Ilwis::Stream::DownloadManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Ilwis__Stream__DownloadManager.data,
    qt_meta_data_Ilwis__Stream__DownloadManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ilwis::Stream::DownloadManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ilwis::Stream::DownloadManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ilwis__Stream__DownloadManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Ilwis::Stream::DownloadManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
