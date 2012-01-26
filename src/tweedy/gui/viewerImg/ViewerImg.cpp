#include <QtGui/QPushButton>
#include <tweedy/core/Projet.hpp>

#include "ViewerImg.h"



ViewerImg::ViewerImg( QWidget* parent ) : QWidget(parent), _labelImg(new QLabel(this)), _imgComposer(new ImageComposer())
{
    setWindowTitle("Visualisation");
    //_labelImg->setScaledContents(true);
    
    //creation des boutons du viewer
    _capture = new QToolButton(this);

    QVBoxLayout * layoutWidget = new QVBoxLayout(this);
    //layoutWidget->addWidget(_labelImg);
    layoutWidget->addWidget(_imgComposer);
        
    layoutWidget->addWidget(_capture);
    setLayout(layoutWidget);

}


void ViewerImg::displayChanged(int time)
{
    /*Timeline* timeline = &(Projet::getInstance().getTimeline());
    std::string  filename = "img/none.jpg";
    
    if (time == timeline->maxTime())
        //afficher le temps reel
        filename = "img/realTime.jpg";
    else
        bool isClip = timeline->findCurrentClip(filename,time);
    
    _labelImg->setPixmap(QPixmap(QString::fromStdString(filename)));*/
}


ViewerImg::~ViewerImg() 
{
    delete _labelImg;
    delete _capture;
}
