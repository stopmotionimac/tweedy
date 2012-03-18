#ifndef GPHOTOWIDGETTOGGLE_HPP
#define GPHOTOWIDGETTOGGLE_HPP

#include <tweedy/core/Projet.hpp>

#include <QtGui/QWidget>
#include <QtGui/QButtonGroup>
#include <QtGui/QRadioButton>

class GPhotoWidgetToggle : public QWidget
{
    Q_OBJECT

private Q_SLOTS:
    void on_setValue_toggled(bool cheked);

 public:
     GPhotoWidgetToggle (CameraWidget* widget);
     CameraWidget * getWidget() { return _widget; }
     QRadioButton * makeButton(const QString name);
//     void putChoicesIntoButtonGroup(const QString name);

 private:
     CameraWidget * _widget;
     QRadioButton * _button;
     std::string _name;
};

#endif // GPHOTOWIDGETTOGGLE_HPP
