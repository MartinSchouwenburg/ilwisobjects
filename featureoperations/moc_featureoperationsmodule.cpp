/****************************************************************************
** Meta object code from reading C++ file 'featureoperationsmodule.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/featureoperationsmodule.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'featureoperationsmodule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Ilwis__FeatureOperations__FeatureOperationsModule_t {
    QByteArrayData data[1];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Ilwis__FeatureOperations__FeatureOperationsModule_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Ilwis__FeatureOperations__FeatureOperationsModule_t qt_meta_stringdata_Ilwis__FeatureOperations__FeatureOperationsModule = {
    {
QT_MOC_LITERAL(0, 0, 49) // "Ilwis::FeatureOperations::Fea..."

    },
    "Ilwis::FeatureOperations::FeatureOperationsModule"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Ilwis__FeatureOperations__FeatureOperationsModule[] = {

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

void Ilwis::FeatureOperations::FeatureOperationsModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Ilwis::FeatureOperations::FeatureOperationsModule::staticMetaObject = { {
    &Module::staticMetaObject,
    qt_meta_stringdata_Ilwis__FeatureOperations__FeatureOperationsModule.data,
    qt_meta_data_Ilwis__FeatureOperations__FeatureOperationsModule,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Ilwis::FeatureOperations::FeatureOperationsModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Ilwis::FeatureOperations::FeatureOperationsModule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Ilwis__FeatureOperations__FeatureOperationsModule.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "n52.org.ilwis.plugin.ilwis.moduleinterface/1.0"))
        return static_cast< Ilwis::Module*>(this);
    return Module::qt_metacast(_clname);
}

int Ilwis::FeatureOperations::FeatureOperationsModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    0x02,  0x78,  0x1b,  'n',  '5',  '2',  '.',  'i', 
    'l',  'w',  'i',  's',  '.',  'f',  'e',  'a', 
    't',  'u',  'r',  'e',  'o',  'p',  'e',  'r', 
    'a',  't',  'i',  'o',  'n',  's', 
    // "className"
    0x03,  0x77,  'F',  'e',  'a',  't',  'u',  'r', 
    'e',  'O',  'p',  'e',  'r',  'a',  't',  'i', 
    'o',  'n',  's',  'M',  'o',  'd',  'u',  'l', 
    'e', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x81, 
    0x71,  'f',  'e',  'a',  't',  'u',  'r',  'e', 
    'o',  'p',  'e',  'r',  'a',  't',  'i',  'o', 
    'n',  's', 
    0xff, 
};
using namespace Ilwis;
using namespace Ilwis::FeatureOperations;
QT_MOC_EXPORT_PLUGIN(Ilwis::FeatureOperations::FeatureOperationsModule, FeatureOperationsModule)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
