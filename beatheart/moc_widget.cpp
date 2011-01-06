/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created: Thu Jan 6 22:07:56 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DesktopGadget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x05,
      43,   15,   14,   14, 0x05,
      65,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      87,   15,   14,   14, 0x0a,
     105,   15,   14,   14, 0x0a,
     123,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DesktopGadget[] = {
    "DesktopGadget\0\0angle\0xRotationChanged(int)\0"
    "yRotationChanged(int)\0zRotationChanged(int)\0"
    "setXRotation(int)\0setYRotation(int)\0"
    "setZRotation(int)\0"
};

const QMetaObject DesktopGadget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_DesktopGadget,
      qt_meta_data_DesktopGadget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DesktopGadget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DesktopGadget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DesktopGadget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DesktopGadget))
        return static_cast<void*>(const_cast< DesktopGadget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int DesktopGadget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setXRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setYRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: setZRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DesktopGadget::xRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DesktopGadget::yRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DesktopGadget::zRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
static const uint qt_meta_data_HeartBeat[] = {

 // content:
       5,       // revision
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

static const char qt_meta_stringdata_HeartBeat[] = {
    "HeartBeat\0"
};

const QMetaObject HeartBeat::staticMetaObject = {
    { &DesktopGadget::staticMetaObject, qt_meta_stringdata_HeartBeat,
      qt_meta_data_HeartBeat, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HeartBeat::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HeartBeat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HeartBeat::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HeartBeat))
        return static_cast<void*>(const_cast< HeartBeat*>(this));
    return DesktopGadget::qt_metacast(_clname);
}

int HeartBeat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DesktopGadget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
