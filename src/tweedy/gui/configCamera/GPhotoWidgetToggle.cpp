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

    projectInstance.gPhotoInstance().getValue(_widget);

    if (this->_name == "yes")
    {
        if (checked)
        {
            std::cout<<"yes"<<std::endl;
            checked = 1;/*normalement pas utile!*/
        }
        else
        {
            std::cout<<"no"<<std::endl;
            checked = 0;
        }
    }
    else
    {
        if (checked)
        {
            std::cout<<"no"<<std::endl;
            checked  = 0;
        }
        else
        {
            std::cout<<"yes"<<std::endl;
            checked = 1;/*normalement pas utile*/
        }
    }
    //PBLEME SEG FAULT
    //projectInstance.gPhotoInstance().setValue(_widget, (const void *)checked);
}
