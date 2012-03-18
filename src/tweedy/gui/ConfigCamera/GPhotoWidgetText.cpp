#include "GPhotoWidgetText.hpp"

GPhotoWidgetText::GPhotoWidgetText(CameraWidget* widget)
{
    _widget = widget;
}

QPushButton * GPhotoWidgetText::makeMenu() {
    _menuChoice = new QMenu(/*this*/);
    QPushButton * buttonChoice = new QPushButton(/*this*/);
    buttonChoice->setMenu(_menuChoice);
    return buttonChoice;


}

void GPhotoWidgetText::putChoicesIntoMenu() {
     Projet& projectInstance = Projet::getInstance();
     int nbChoices = projectInstance.gPhotoInstance().CountChoices(_widget);
     //std::vector<QAction * > actionList;

     for (int j = 0; j< nbChoices; ++j) {
         std::string choiceName = projectInstance.gPhotoInstance().getChoice(_widget, j);
         //std::cout<<"NAME CHOICE => "<<choiceName<<std::endl;
         //menuChoice->addMenu(QString::fromStdString(choiceName));

         /*make the appropriate action*/


//         actionList.push_back(new QAction(QString::fromStdString(choiceName), this));
//         _menuChoice->addAction(actionList.at(j));
//         connect(actionList.at(j), SIGNAL(triggered()), this, SLOT(on_setValue_triggered()));


         _setValue = new QAction(QString::fromStdString(choiceName), this);
         //_setValue = _menuChoice->addAction(QString::fromStdString(choiceName));
         //sert a rien
         //_menuChoice->setDefaultAction(_setValue);
         _menuChoice->addAction(_setValue);
         connect(_setValue, SIGNAL(triggered()), this, SLOT(on_setValue_triggered()));

     }
}

void GPhotoWidgetText::on_setValue_triggered() {
    std::cout<<"OK on_setValue"<<std::endl;
//    GARDE LE TEXTE DE LA DERNIERE ACTION => NORMAL!!!
//    QString val = _setValue->text();
//    std::string valS = val.toStdString();
//    std::cout<<"VAL ACTION : "<<valS<<std::endl;
}
