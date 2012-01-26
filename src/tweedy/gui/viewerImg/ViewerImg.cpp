#include <QtGui/QPushButton>
#include <tweedy/core/Projet.hpp>

#include "ViewerImg.h"



ViewerImg::ViewerImg( QWidget* parent ) : QWidget(parent), _labelImg(new QLabel(this)) 
{
    setWindowTitle("Visualisation");
    _labelImg->setScaledContents(true);
    
    //creation des boutons du viewer
    _capture = new QToolButton(this);
    /*_playButton = new QToolButton(this);
    _nextButton = new QToolButton(this);
    _previousButton = new QToolButton(this);

    QHBoxLayout * layoutHPlayer = new QHBoxLayout(this);
    layoutHPlayer->addWidget(_capture);
    layoutHPlayer->addStretch();
    layoutHPlayer->addWidget(_previousButton);
    layoutHPlayer->addWidget(_playButton);
    layoutHPlayer->addWidget(_nextButton);
    layoutHPlayer->addStretch();*/

    /*QVBoxLayout * layoutVPlayer = new QVBoxLayout(this);
    layoutVPlayer->addStretch();
    layoutVPlayer->addLayout(layoutHPlayer);
    layoutVPlayer->addStretch();

    QHBoxLayout * layoutBoutons = new QHBoxLayout(this);
    layoutBoutons->addWidget(_capture);
    layoutBoutons->addLayout(layoutVPlayer);*/

    QVBoxLayout * layoutWidget = new QVBoxLayout(this);
    layoutWidget->addWidget(_labelImg);
        
    layoutWidget->addWidget(_capture);
    setLayout(layoutWidget);

}

void ViewerImg::displayImg(std::string filename)
{
   _labelImg->setPixmap(QPixmap(QString::fromStdString(filename)));
}  

void ViewerImg::displayChanged(int time)
{
    Timeline* timeline = &(Projet::getInstance().getTimeline());
    std::string  filename = "img/none.jpg";
    
    if (time == timeline->maxTime())
        //afficher le temps reel
        filename = "img/realTime.jpg";
    else
        bool isClip = timeline->findCurrentClip(filename,time);
    
    _labelImg->setPixmap(QPixmap(QString::fromStdString(filename)));
}


ViewerImg::~ViewerImg() 
{
    delete _labelImg;
    delete _capture;
}
