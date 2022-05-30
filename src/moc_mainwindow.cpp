/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[28];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "newSpeedForStreet"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 8), // "newspeed"
QT_MOC_LITERAL(4, 39, 4), // "zoom"
QT_MOC_LITERAL(5, 44, 1), // "z"
QT_MOC_LITERAL(6, 46, 7), // "getTime"
QT_MOC_LITERAL(7, 54, 8), // "setSpeed"
QT_MOC_LITERAL(8, 63, 1), // "x"
QT_MOC_LITERAL(9, 65, 14), // "resetTimeLabel"
QT_MOC_LITERAL(10, 80, 10), // "cancelRoad"
QT_MOC_LITERAL(11, 91, 12), // "generateInfo"
QT_MOC_LITERAL(12, 104, 8), // "Vehicle*"
QT_MOC_LITERAL(13, 113, 13), // "generateLabel"
QT_MOC_LITERAL(14, 127, 9), // "paintRoad"
QT_MOC_LITERAL(15, 137, 2), // "x1"
QT_MOC_LITERAL(16, 140, 2), // "y1"
QT_MOC_LITERAL(17, 143, 2), // "x2"
QT_MOC_LITERAL(18, 146, 2), // "y2"
QT_MOC_LITERAL(19, 149, 8), // "lineName"
QT_MOC_LITERAL(20, 158, 12), // "clearBusInfo"
QT_MOC_LITERAL(21, 171, 11), // "enableCombo"
QT_MOC_LITERAL(22, 183, 7), // "Street*"
QT_MOC_LITERAL(23, 191, 7), // "pressed"
QT_MOC_LITERAL(24, 199, 18), // "streetSpeedChanged"
QT_MOC_LITERAL(25, 218, 9), // "new_speed"
QT_MOC_LITERAL(26, 228, 15), // "ptrClosedStreet"
QT_MOC_LITERAL(27, 244, 6) // "closed"

    },
    "MainWindow\0newSpeedForStreet\0\0newspeed\0"
    "zoom\0z\0getTime\0setSpeed\0x\0resetTimeLabel\0"
    "cancelRoad\0generateInfo\0Vehicle*\0"
    "generateLabel\0paintRoad\0x1\0y1\0x2\0y2\0"
    "lineName\0clearBusInfo\0enableCombo\0"
    "Street*\0pressed\0streetSpeedChanged\0"
    "new_speed\0ptrClosedStreet\0closed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   82,    2, 0x08 /* Private */,
       6,    0,   85,    2, 0x08 /* Private */,
       7,    1,   86,    2, 0x08 /* Private */,
       9,    0,   89,    2, 0x08 /* Private */,
      10,    0,   90,    2, 0x0a /* Public */,
      11,    1,   91,    2, 0x0a /* Public */,
      13,    4,   94,    2, 0x0a /* Public */,
      14,    5,  103,    2, 0x0a /* Public */,
      20,    0,  114,    2, 0x0a /* Public */,
      21,    1,  115,    2, 0x0a /* Public */,
      24,    1,  118,    2, 0x0a /* Public */,
      26,    1,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QReal, 0x80000000 | 12,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString,   15,   16,   17,   18,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, 0x80000000 | 22,   27,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newSpeedForStreet((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->zoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->getTime(); break;
        case 3: _t->setSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->resetTimeLabel(); break;
        case 5: _t->cancelRoad(); break;
        case 6: _t->generateInfo((*reinterpret_cast< Vehicle*(*)>(_a[1]))); break;
        case 7: _t->generateLabel((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3])),(*reinterpret_cast< Vehicle*(*)>(_a[4]))); break;
        case 8: _t->paintRoad((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 9: _t->clearBusInfo(); break;
        case 10: _t->enableCombo((*reinterpret_cast< Street*(*)>(_a[1]))); break;
        case 11: _t->streetSpeedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->ptrClosedStreet((*reinterpret_cast< Street*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Vehicle* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Vehicle* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Street* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Street* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::newSpeedForStreet)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::newSpeedForStreet(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
