/****************************************************************************
** Meta object code from reading C++ file 'functionwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/functionwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'functionwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FunctionWindow_t {
    QByteArrayData data[19];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FunctionWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FunctionWindow_t qt_meta_stringdata_FunctionWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FunctionWindow"
QT_MOC_LITERAL(1, 15, 16), // "graphLegendClick"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 10), // "QCPLegend*"
QT_MOC_LITERAL(4, 44, 1), // "l"
QT_MOC_LITERAL(5, 46, 22), // "QCPAbstractLegendItem*"
QT_MOC_LITERAL(6, 69, 2), // "ai"
QT_MOC_LITERAL(7, 72, 12), // "QMouseEvent*"
QT_MOC_LITERAL(8, 85, 2), // "me"
QT_MOC_LITERAL(9, 88, 10), // "graphClick"
QT_MOC_LITERAL(10, 99, 21), // "QCPAbstractPlottable*"
QT_MOC_LITERAL(11, 121, 9), // "plottable"
QT_MOC_LITERAL(12, 131, 15), // "changeCurrentIO"
QT_MOC_LITERAL(13, 147, 13), // "changeIORange"
QT_MOC_LITERAL(14, 161, 14), // "insertFunction"
QT_MOC_LITERAL(15, 176, 14), // "deleteFunction"
QT_MOC_LITERAL(16, 191, 18), // "deleteAllFunctions"
QT_MOC_LITERAL(17, 210, 12), // "editFunction"
QT_MOC_LITERAL(18, 223, 21) // "currentFunctionSugeno"

    },
    "FunctionWindow\0graphLegendClick\0\0"
    "QCPLegend*\0l\0QCPAbstractLegendItem*\0"
    "ai\0QMouseEvent*\0me\0graphClick\0"
    "QCPAbstractPlottable*\0plottable\0"
    "changeCurrentIO\0changeIORange\0"
    "insertFunction\0deleteFunction\0"
    "deleteAllFunctions\0editFunction\0"
    "currentFunctionSugeno"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FunctionWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   59,    2, 0x08 /* Private */,
       9,    2,   66,    2, 0x08 /* Private */,
      12,    0,   71,    2, 0x08 /* Private */,
      13,    0,   72,    2, 0x08 /* Private */,
      14,    0,   73,    2, 0x08 /* Private */,
      15,    0,   74,    2, 0x08 /* Private */,
      16,    0,   75,    2, 0x08 /* Private */,
      17,    0,   76,    2, 0x08 /* Private */,
      18,    0,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 7,   11,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FunctionWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FunctionWindow *_t = static_cast<FunctionWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->graphLegendClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 1: _t->graphClick((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< QMouseEvent*(*)>(_a[2]))); break;
        case 2: _t->changeCurrentIO(); break;
        case 3: _t->changeIORange(); break;
        case 4: _t->insertFunction(); break;
        case 5: _t->deleteFunction(); break;
        case 6: _t->deleteAllFunctions(); break;
        case 7: _t->editFunction(); break;
        case 8: _t->currentFunctionSugeno(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        }
    }
}

const QMetaObject FunctionWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FunctionWindow.data,
      qt_meta_data_FunctionWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FunctionWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FunctionWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FunctionWindow.stringdata0))
        return static_cast<void*>(const_cast< FunctionWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int FunctionWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
