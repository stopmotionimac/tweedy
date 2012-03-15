#include "GPhotoWidgetTextItems.hpp"

GPhotoWidgetTextItems::GPhotoWidgetTextItems(CameraWidget* widget)
{
    _widget = widget;
}

QComboBox * GPhotoWidgetTextItems::makeMenu() {
//    _menuChoice = new QMenu(/*this*/);
//    QPushButton * buttonChoice = new QPushButton(/*this*/);
//    buttonChoice->setMenu(_menuChoice);
//    return buttonChoice;
    _comboBoxChoice = new QComboBox(/*this*/);
    return _comboBoxChoice;


}

void GPhotoWidgetTextItems::putChoicesIntoMenu() {
    Projet& projectInstance = Projet::getInstance();
    int nbChoices = projectInstance.gPhotoInstance().CountChoices(_widget);

    for (int j = 0; j< nbChoices; ++j) {
        std::string choiceName = projectInstance.gPhotoInstance().getChoice(_widget, j);
        _comboBoxChoice->addItem(QString::fromStdString(choiceName));

        //QObject::connect(combo, SIGNAL(activated(int)),label, SLOT(hide()));

        /*make the appropriate action*/
        QComboBox::connect(_comboBoxChoice, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(on_setValue_activated(const QString&)));
    }

}

void GPhotoWidgetTextItems::on_setValue_activated(const QString & valueChoice){
    //std::cout<<valueChoice.toStdString() <<std::endl;
    const void * varChoice = valueChoice.toStdString().data();
    Projet& projectInstance = Projet::getInstance();
    projectInstance.gPhotoInstance().setValue(_widget, valueChoice.toStdString().data());
}
