#include "GPhotoWidgetToggle.hpp"

GPhotoWidgetToggle::GPhotoWidgetToggle(CameraWidget * widget)
{
    _widget = widget;
}

QRadioButton * GPhotoWidgetToggle::makeButton(const QString name) {
    this->_name = name.toStdString();
    _button = new QRadioButton(name);
    QRadioButton::connect(_button, SIGNAL(toggled(bool)), this, SLOT(on_setValue_toggled(bool)));
    return _button;
}

//void GPhotoWidgetToggle::putChoicesIntoButtonGroup(const QString name) {
//    Projet& projectInstance = Projet::getInstance();

////    QRadioButton * yesChoice = new QRadioButton("yes"/*, this*/);
////    QRadioButton * noChoice = new QRadioButton("no"/*, this*/);
////    _buttonGourp->addButton(yesChoice);
////    _buttonGourp->addButton(noChoice);

//    QRadioButton::connect(_button, SIGNAL(ButtonReleased(int)), this, SLOT(on_setValue_released(int)));
//}

void GPhotoWidgetToggle::on_setValue_toggled(bool checked){
      //std::cout<<this->_name<<std::endl;
    Projet& projectInstance = Projet::getInstance();
    projectInstance.gPhotoInstance().setValue(_widget, (const void *)checked);

    if (this->_name == "yes")
    {
        if (checked)
        {
            checked = 1;/*normalement pas utile!*/
        }
        else
        {
            checked = 0;
        }
    }
    else
    {
        if (checked)
        {
            checked  = 0;
        }
        else
        {
            checked = 1;/*normalement pas utile*/
        }
    }
    projectInstance.gPhotoInstance().setValue(_widget, (const void *)checked);

//    const void * varChoice = valueChoice.toStdString().data();
//    Projet& projectInstance = Projet::getInstance();
//    projectInstance.gPhotoInstance().setValue(_widget, valueChoice.toStdString().data());
}
