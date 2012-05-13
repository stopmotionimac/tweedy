#ifndef GPHOTOWIDGETTEXTITEMS_HPP
#define GPHOTOWIDGETTEXTITEMS_HPP

#include <tweedy/core/Projet.hpp>

#include <QtGui/QWidget>
#include <QtGui/QComboBox>

class GPhotoWidgetTextItems : public QWidget
{
    Q_OBJECT

private Q_SLOTS:
   void on_setValue_activated(const QString & valueChoice);

public:
    GPhotoWidgetTextItems (CameraWidget* widget);
    CameraWidget * getWidget() { return _widget; }
    QComboBox * makeMenu();
    void putChoicesIntoMenu();

private:
    CameraWidget * _widget;
    QComboBox * _comboBoxChoice;
};

#endif // GPHOTOWIDGETTEXTITEMS_HPP
