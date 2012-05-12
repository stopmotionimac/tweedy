#include "GPhotoWidgetTextItems.hpp"

GPhotoWidgetTextItems::GPhotoWidgetTextItems(CameraWidget* widget)
{
    _widget = widget;
}

QComboBox * GPhotoWidgetTextItems::makeMenu() {
    _comboBoxChoice = new QComboBox();
    return _comboBoxChoice;
}

void GPhotoWidgetTextItems::putChoicesIntoMenu() {
    Projet& projectInstance = Projet::getInstance();
    int nbChoices = projectInstance.gPhotoInstance().CountChoices(_widget);

    for (int j = 0; j< nbChoices; ++j) {
        std::string choiceName = projectInstance.gPhotoInstance().getChoice(_widget, j);
        _comboBoxChoice->addItem(QString::fromStdString(choiceName));

        /*make the appropriate action*/
        QComboBox::connect(_comboBoxChoice, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(on_setValue_activated(const QString&)));
    }
}

void GPhotoWidgetTextItems::on_setValue_activated(const QString & valueChoice){
    Projet& projectInstance = Projet::getInstance();
    projectInstance.gPhotoInstance().setValueString(_widget, valueChoice.toStdString().data());
}
