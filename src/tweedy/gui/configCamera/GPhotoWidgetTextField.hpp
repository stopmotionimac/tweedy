#ifndef GPHOTOWIDGETTEXTFILED_HPP
#define GPHOTOWIDGETTEXTFILED_HPP

#include <tweedy/core/Projet.hpp>

#include <QtGui/QWidget>
#include <QtGui/QLineEdit>

class GPhotoWidgetTextField : public QWidget
{
    Q_OBJECT

private Q_SLOTS:
   void on_setValue_textChanged(const QString & valueChoice);

public:
    GPhotoWidgetTextField (CameraWidget* widget);
    CameraWidget * getWidget() { return _widget; }
    QLineEdit * makeMenu();

private:
    CameraWidget * _widget;
    QLineEdit * _textField;
};

#endif // GPHOTOWIDGETTEXTFILED_HPP
