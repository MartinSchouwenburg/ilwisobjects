/****************************************************************************
** Meta object code from reading C++ file 'baseoperationsmodule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/baseoperationsmodule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'baseoperationsmodule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ilwis__BaseOperations__BaseOperationsModule_t {
    QByteArrayData data[1];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ilwis__BaseOperations__BaseOperationsModule_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ilwis__BaseOperations__BaseOperationsModule_t qt_meta_stringdata_Ilwis__BaseOperations__BaseOperationsModule = {
    {
QT_MOC_LITERAL(0, 0, 43) // "Ilwis::BaseOperations::BaseOp..."

    },
    "Ilwis::BaseOperations::BaseOperationsModule"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ilwis__BaseOperations__BaseOperationsModule[] = {

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

void Ilwis::BaseOperations::BaseOperationsModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Ilwis::BaseOperations::BaseOperationsModule::staticMetaObject = { {
    &Module::staticMetaObject,
    qt_meta_stringdata_Ilwis__BaseOperations__BaseOperationsModule.data,
    qt_meta_data_Ilwis__BaseOperations__BaseOperationsModule,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ilwis::BaseOperations::BaseOperationsModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ilwis::BaseOperations::BaseOperationsModule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ilwis__BaseOperations__BaseOperationsModule.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "n52.org.ilwis.plugin.ilwis.moduleinterface/1.0"))
        return static_cast< Ilwis::Module*>(this);
    return Module::qt_metacast(_clname);
}

int Ilwis::BaseOperations::BaseOperationsModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Module::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x18,  'n',  '5',  '2',  '.',  'i', 
    'l',  'w',  'i',  's',  '.',  'b',  'a',  's', 
    'e',  'o',  'p',  'e',  'r',  'a',  't',  'i', 
    'o',  'n',  's', 
    // "className"
    0x03,  0x74,  'B',  'a',  's',  'e',  'O',  'p', 
    'e',  'r',  'a',  't',  'i',  'o',  'n',  's', 
    'M',  'o',  'd',  'u',  'l',  'e', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x81, 
    0x6e,  'b',  'a',  's',  'e',  'o',  'p',  'e', 
    'r',  'a',  't',  'i',  'o',  'n',  's', 
    0xff, 
};
using namespace Ilwis;
using namespace Ilwis::BaseOperations;
QT_MOC_EXPORT_PLUGIN(Ilwis::BaseOperations::BaseOperationsModule, BaseOperationsModule)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
