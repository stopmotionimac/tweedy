#ifndef GPHOTOWIDGETTEXT_HPP
#define GPHOTOWIDGETTEXT_HPP

#include <tweedy/core/Projet.hpp>

#include <QtGui/QWidget>
#include <QtGui/QToolButton>
#include <QtGui/QLabel>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QMenu>
#include <QtGui/QRadioButton>
#include <QtGui/QLineEdit>
#include <QtGui/QComboBox>


class GPhotoWidgetText : public QWidget
{
    Q_OBJECT

private Q_SLOTS:
   void on_setValue_triggered();

Q_SIGNALS:
    void setValueToGPhoto(CameraWidget * widget, const void *value);




public:
    GPhotoWidgetText (CameraWidget* widget);
    CameraWidget * getWidget() { return _widget; }
    QPushButton * makeMenu();
    void putChoicesIntoMenu();

private:
    CameraWidget * _widget;
    QMenu * _menuChoice;
    QComboBox * _comboBoxChoice;

private:

   QAction * _setValue;
};

#endif // GPHOTOWIDGETTEXT_HPP
