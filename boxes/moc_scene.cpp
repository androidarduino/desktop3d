/****************************************************************************
** Meta object code from reading C++ file 'scene.h'
**
** Created: Thu Jan 6 10:42:49 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ColorEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ColorEdit[] = {
    "ColorEdit\0\0color,id\0colorChanged(QRgb,int)\0"
    "editDone()\0"
};

const QMetaObject ColorEdit::staticMetaObject = {
    { &ParameterEdit::staticMetaObject, qt_meta_stringdata_ColorEdit,
      qt_meta_data_ColorEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ColorEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ColorEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ColorEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ColorEdit))
        return static_cast<void*>(const_cast< ColorEdit*>(this));
    return ParameterEdit::qt_metacast(_clname);
}

int ColorEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ParameterEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: colorChanged((*reinterpret_cast< QRgb(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: editDone(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ColorEdit::colorChanged(QRgb _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_FloatEdit[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FloatEdit[] = {
    "FloatEdit\0\0value,id\0valueChanged(float,int)\0"
    "editDone()\0"
};

const QMetaObject FloatEdit::staticMetaObject = {
    { &ParameterEdit::staticMetaObject, qt_meta_stringdata_FloatEdit,
      qt_meta_data_FloatEdit, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FloatEdit::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FloatEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FloatEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FloatEdit))
        return static_cast<void*>(const_cast< FloatEdit*>(this));
    return ParameterEdit::qt_metacast(_clname);
}

int FloatEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ParameterEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: editDone(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FloatEdit::valueChanged(float _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_TwoSidedGraphicsWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x0a,
      31,   23,   23,   23, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_TwoSidedGraphicsWidget[] = {
    "TwoSidedGraphicsWidget\0\0flip()\0"
    "animateFlip()\0"
};

const QMetaObject TwoSidedGraphicsWidget::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TwoSidedGraphicsWidget,
      qt_meta_data_TwoSidedGraphicsWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TwoSidedGraphicsWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TwoSidedGraphicsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TwoSidedGraphicsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TwoSidedGraphicsWidget))
        return static_cast<void*>(const_cast< TwoSidedGraphicsWidget*>(this));
    return QObject::qt_metacast(_clname);
}

int TwoSidedGraphicsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: flip(); break;
        case 1: animateFlip(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_RenderOptionsDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      50,   48,   20,   20, 0x05,
      86,   48,   20,   20, 0x05,
     123,   20,   20,   20, 0x05,
     143,   20,   20,   20, 0x05,
     162,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
     187,  178,   20,   20, 0x09,
     224,  215,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_RenderOptionsDialog[] = {
    "RenderOptionsDialog\0\0dynamicCubemapToggled(int)\0"
    ",\0colorParameterChanged(QString,QRgb)\0"
    "floatParameterChanged(QString,float)\0"
    "textureChanged(int)\0shaderChanged(int)\0"
    "doubleClicked()\0color,id\0"
    "setColorParameter(QRgb,int)\0value,id\0"
    "setFloatParameter(float,int)\0"
};

const QMetaObject RenderOptionsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RenderOptionsDialog,
      qt_meta_data_RenderOptionsDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RenderOptionsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RenderOptionsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RenderOptionsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderOptionsDialog))
        return static_cast<void*>(const_cast< RenderOptionsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int RenderOptionsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dynamicCubemapToggled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: colorParameterChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QRgb(*)>(_a[2]))); break;
        case 2: floatParameterChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: textureChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: shaderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: doubleClicked(); break;
        case 6: setColorParameter((*reinterpret_cast< QRgb(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: setFloatParameter((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void RenderOptionsDialog::dynamicCubemapToggled(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RenderOptionsDialog::colorParameterChanged(const QString & _t1, QRgb _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RenderOptionsDialog::floatParameterChanged(const QString & _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RenderOptionsDialog::textureChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RenderOptionsDialog::shaderChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void RenderOptionsDialog::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
static const uint qt_meta_data_ItemDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      33,   28,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,   11,   11,   11, 0x0a,
      90,   11,   11,   11, 0x0a,
     113,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ItemDialog[] = {
    "ItemDialog\0\0doubleClicked()\0type\0"
    "newItemTriggered(ItemDialog::ItemType)\0"
    "triggerNewQtBox()\0triggerNewCircleItem()\0"
    "triggerNewSquareItem()\0"
};

const QMetaObject ItemDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ItemDialog,
      qt_meta_data_ItemDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ItemDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ItemDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ItemDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ItemDialog))
        return static_cast<void*>(const_cast< ItemDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ItemDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: doubleClicked(); break;
        case 1: newItemTriggered((*reinterpret_cast< ItemDialog::ItemType(*)>(_a[1]))); break;
        case 2: triggerNewQtBox(); break;
        case 3: triggerNewCircleItem(); break;
        case 4: triggerNewSquareItem(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ItemDialog::doubleClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ItemDialog::newItemTriggered(ItemDialog::ItemType _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_Scene[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,    7,    6,    6, 0x0a,
      28,    7,    6,    6, 0x0a,
      50,   44,    6,    6, 0x0a,
      87,   76,    6,    6, 0x0a,
     130,  119,    6,    6, 0x0a,
     168,  163,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Scene[] = {
    "Scene\0\0index\0setShader(int)\0setTexture(int)\0"
    "state\0toggleDynamicCubemap(int)\0"
    "name,color\0setColorParameter(QString,QRgb)\0"
    "name,value\0setFloatParameter(QString,float)\0"
    "type\0newItem(ItemDialog::ItemType)\0"
};

const QMetaObject Scene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_Scene,
      qt_meta_data_Scene, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Scene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Scene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Scene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Scene))
        return static_cast<void*>(const_cast< Scene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int Scene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setShader((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setTexture((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: toggleDynamicCubemap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setColorParameter((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QRgb(*)>(_a[2]))); break;
        case 4: setFloatParameter((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: newItem((*reinterpret_cast< ItemDialog::ItemType(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
