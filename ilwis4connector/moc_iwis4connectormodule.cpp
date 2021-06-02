/****************************************************************************
** Meta object code from reading C++ file 'iwis4connectormodule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/iwis4connectormodule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iwis4connectormodule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ilwis__Ilwis4C__Ilwis4ConnectorModule_t {
    QByteArrayData data[1];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ilwis__Ilwis4C__Ilwis4ConnectorModule_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ilwis__Ilwis4C__Ilwis4ConnectorModule_t qt_meta_stringdata_Ilwis__Ilwis4C__Ilwis4ConnectorModule = {
    {
QT_MOC_LITERAL(0, 0, 37) // "Ilwis::Ilwis4C::Ilwis4Connect..."

    },
    "Ilwis::Ilwis4C::Ilwis4ConnectorModule"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ilwis__Ilwis4C__Ilwis4ConnectorModule[] = {

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

void Ilwis::Ilwis4C::Ilwis4ConnectorModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Ilwis::Ilwis4C::Ilwis4ConnectorModule::staticMetaObject = { {
    &Module::staticMetaObject,
    qt_meta_stringdata_Ilwis__Ilwis4C__Ilwis4ConnectorModule.data,
    qt_meta_data_Ilwis__Ilwis4C__Ilwis4ConnectorModule,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ilwis::Ilwis4C::Ilwis4ConnectorModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ilwis::Ilwis4C::Ilwis4ConnectorModule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ilwis__Ilwis4C__Ilwis4ConnectorModule.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "n52.org.ilwis.plugin.ilwis.moduleinterface/1.0"))
        return static_cast< Ilwis::Module*>(this);
    return Module::qt_metacast(_clname);
}

int Ilwis::Ilwis4C::Ilwis4ConnectorModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    0x02,  0x78,  0x1f,  'n',  '5',  '2',  '.',  'i', 
    'l',  'w',  'i',  's',  '.',  'I',  'l',  'w', 
    'i',  's',  '4',  'C',  'o',  'n',  'n',  'e', 
    'c',  't',  'o',  'r',  'M',  'o',  'd',  'u', 
    'l',  'e', 
    // "className"
    0x03,  0x75,  'I',  'l',  'w',  'i',  's',  '4', 
    'C',  'o',  'n',  'n',  'e',  'c',  't',  'o', 
    'r',  'M',  'o',  'd',  'u',  'l',  'e', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x81, 
    0x6f,  'i',  'l',  'w',  'i',  's',  '4',  'c', 
    'o',  'n',  'n',  'e',  'c',  't',  'o',  'r', 
    0xff, 
};
using namespace Ilwis;
using namespace Ilwis::Ilwis4C;
QT_MOC_EXPORT_PLUGIN(Ilwis::Ilwis4C::Ilwis4ConnectorModule, Ilwis4ConnectorModule)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
