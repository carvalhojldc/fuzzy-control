/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "connectServer"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "UI_configGraphs"
QT_MOC_LITERAL(4, 42, 15), // "UI_DisplayGraph"
QT_MOC_LITERAL(5, 58, 17), // "UI_functionWindow"
QT_MOC_LITERAL(6, 76, 13), // "UI_ruleWindow"
QT_MOC_LITERAL(7, 90, 12), // "controlInput"
QT_MOC_LITERAL(8, 103, 2), // "id"
QT_MOC_LITERAL(9, 106, 13), // "carrierSignal"
QT_MOC_LITERAL(10, 120, 7), // "voltage"
QT_MOC_LITERAL(11, 128, 6), // "travel"
QT_MOC_LITERAL(12, 135, 16), // "calculatedSignal"
QT_MOC_LITERAL(13, 152, 11), // "tankLevel_2"
QT_MOC_LITERAL(14, 164, 14), // "myFuzzyControl"
QT_MOC_LITERAL(15, 179, 7), // "myGraph"
QT_MOC_LITERAL(16, 187, 17), // "UI_limitRandInput"
QT_MOC_LITERAL(17, 205, 15), // "UI_configSignal"
QT_MOC_LITERAL(18, 221, 6), // "signal"
QT_MOC_LITERAL(19, 228, 10), // "updateData"
QT_MOC_LITERAL(20, 239, 13) // "MandSugStatus"

    },
    "MainWindow\0connectServer\0\0UI_configGraphs\0"
    "UI_DisplayGraph\0UI_functionWindow\0"
    "UI_ruleWindow\0controlInput\0id\0"
    "carrierSignal\0voltage\0travel\0"
    "calculatedSignal\0tankLevel_2\0"
    "myFuzzyControl\0myGraph\0UI_limitRandInput\0"
    "UI_configSignal\0signal\0updateData\0"
    "MandSugStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    1,   89,    2, 0x08 /* Private */,
       9,    1,   92,    2, 0x08 /* Private */,
      11,    2,   95,    2, 0x08 /* Private */,
      14,    0,  100,    2, 0x08 /* Private */,
      15,    0,  101,    2, 0x08 /* Private */,
      16,    0,  102,    2, 0x08 /* Private */,
      17,    1,  103,    2, 0x08 /* Private */,
      19,    0,  106,    2, 0x08 /* Private */,
      20,    0,  107,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Double, QMetaType::Double,   10,
    QMetaType::Double, QMetaType::Double, QMetaType::Double,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectServer(); break;
        case 1: _t->UI_configGraphs(); break;
        case 2: _t->UI_DisplayGraph(); break;
        case 3: _t->UI_functionWindow(); break;
        case 4: _t->UI_ruleWindow(); break;
        case 5: _t->controlInput((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { double _r = _t->carrierSignal((*reinterpret_cast< double(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 7: { double _r = _t->travel((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 8: _t->myFuzzyControl(); break;
        case 9: _t->myGraph(); break;
        case 10: _t->UI_limitRandInput(); break;
        case 11: _t->UI_configSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->updateData(); break;
        case 13: _t->MandSugStatus(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Signal"))
        return static_cast< Signal*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
