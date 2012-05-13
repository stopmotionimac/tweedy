#ifndef __CONFIGCAMERA_HPP__
#define __CONFIGCAMERA_HPP__

#include <tweedy/core/Projet.hpp>

#include <tweedy/gui/configCamera/GPhotoWidgetTextItems.hpp>
#include <tweedy/gui/configCamera/GPhotoWidgetTextField.hpp>
#include <tweedy/gui/configCamera/GPhotoWidgetToggle.hpp>

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>

class ConfigCamera : public QWidget
{
    Q_OBJECT

public:
   ConfigCamera(QWidget *parent = 0);
    ~ConfigCamera(){}

private Q_SLOTS:

};

#endif // __CONFIGCAMERA_HPP__

