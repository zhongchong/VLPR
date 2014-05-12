/****************************************************************************
** Meta object code from reading C++ file 'vlpr.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vlpr.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vlpr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VLPR[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      29,    5,    5,    5, 0x08,
      47,    5,    5,    5, 0x08,
      71,    5,    5,    5, 0x08,
      95,    5,    5,    5, 0x08,
     114,    5,    5,    5, 0x08,
     128,    5,    5,    5, 0x08,
     146,    5,    5,    5, 0x08,
     166,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VLPR[] = {
    "VLPR\0\0on_OpenImage_clicked()\0"
    "on_Gray_clicked()\0on_Show_Image_clicked()\0"
    "on_edgeDetect_clicked()\0on_thres_clicked()\0"
    "dilateErode()\0on_blur_clicked()\0"
    "on_locate_clicked()\0on_charCut_clicked()\0"
};

void VLPR::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VLPR *_t = static_cast<VLPR *>(_o);
        switch (_id) {
        case 0: _t->on_OpenImage_clicked(); break;
        case 1: _t->on_Gray_clicked(); break;
        case 2: _t->on_Show_Image_clicked(); break;
        case 3: _t->on_edgeDetect_clicked(); break;
        case 4: _t->on_thres_clicked(); break;
        case 5: _t->dilateErode(); break;
        case 6: _t->on_blur_clicked(); break;
        case 7: _t->on_locate_clicked(); break;
        case 8: _t->on_charCut_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData VLPR::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VLPR::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_VLPR,
      qt_meta_data_VLPR, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VLPR::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VLPR::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VLPR::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VLPR))
        return static_cast<void*>(const_cast< VLPR*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int VLPR::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
