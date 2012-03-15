#ifndef __CONFIGCAMERA_HPP__
#define __CONFIGCAMERA_HPP__

#include <tweedy/core/Projet.hpp>

#include <tweedy/gui/configCamera/GPhotoWidgetTextItems.hpp>
#include <tweedy/gui/configCamera/GPhotoWidgetTextField.hpp>
#include <tweedy/gui/configCamera/GPhotoWidgetToggle.hpp>

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


class ConfigCamera : public QWidget
{
    Q_OBJECT

public:
   ConfigCamera(QWidget *parent);
    ~ConfigCamera(){}


/*public slots:
   void changeValueSlot(int i);

   signals:
   void changeValueSignal(int i);
*/

/*Q_SIGNALS:
   void changeValueSignal(int i);
*/

private Q_SLOTS:
   //void on_setValue_triggered(/*CameraWidget * widget, const void *value*/);
   //void on_setValueToGPhoto(CameraWidget * widget, const void *value);

//private:

//   QAction * _setValue;

};

#endif // __CONFIGCAMERA_HPP__

