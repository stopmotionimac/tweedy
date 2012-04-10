#include "GPhotoWidgetToggle.hpp"

GPhotoWidgetToggle::GPhotoWidgetToggle(CameraWidget * widget)
{
    _widget = widget;
}

QRadioButton * GPhotoWidgetToggle::makeButton(const QString name) {
    this->_name = name.toStdString();
    _button = new QRadioButton(name);
    /*make the appropriate action*/
    QRadioButton::connect(_button, SIGNAL(toggled(bool)), this, SLOT(on_setValue_toggled(bool)));
    return _button;
}

void GPhotoWidgetToggle::on_setValue_toggled(bool checked){

    //Gphoto needs 2 for "yes" and 0 for "no"!
    int value;
    Projet& projectInstance = Projet::getInstance();

    projectInstance.gPhotoInstance().getValue(_widget);

    if (this->_name == "yes")
    {
        if (checked)
        {
            value = 2;
        }
        else
        {
            value = 0;
        }
    }
    else
    {
        if (checked)
        {
            value = 0;
        }
        else
        {
            value = 2;
        }
    }
    projectInstance.gPhotoInstance().setValueInt(_widget, value);

}
