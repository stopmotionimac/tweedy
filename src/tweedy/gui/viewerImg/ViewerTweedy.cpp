#include "ViewerTweedy.h"
#include "ui_ViewerTweedy.h"

#include <tweedy/core/Projet.hpp>

ViewerTweedy::ViewerTweedy(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ViewerTweedy)
{
    _ui->setupUi(this);
}


QToolButton * ViewerTweedy::getPlayPauseButton() { return _ui->playPauseButton; }

QToolButton * ViewerTweedy::getNextButton() { return _ui->nextButton; }

QToolButton * ViewerTweedy::getPreviousButton() { return _ui->previousButton; }

QToolButton * ViewerTweedy::getCaptureButton() { return _ui->captureButton; }

QLabel * ViewerTweedy::getViewerLabel() { return _ui->viewerLabel; }


void ViewerTweedy::displayImg(std::string filename)
{
   this->getViewerLabel()->setPixmap(QPixmap(QString::fromStdString(filename)));
}


void ViewerTweedy::displayChanged(int time)
{
    /*Timeline* timeline = &(Projet::getInstance().getTimeline());
    std::string  filename = "img/none.jpg";

    if (time == timeline->maxTime())
        //afficher le temps reel
        filename = "img/realTime.jpg";
    else
        bool isClip = timeline->findCurrentClip(filename,time);

    this->getViewerLabel()->setPixmap(QPixmap(QString::fromStdString(filename)));*/
   
     
    
    QImage sourceImage("img/tweedy2.jpg");
    QImage destinationImage("img/tweedy3.jpg");
    QImage resultImage = QImage(QSize(475,343), QImage::Format_ARGB32_Premultiplied);
    
    QPainter::CompositionMode mode = QPainter::CompositionMode_SoftLight;

    QPainter painter(&resultImage);
     
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, destinationImage);
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, sourceImage);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::white);
    painter.end();

    this->getViewerLabel()->setPixmap(QPixmap::fromImage(resultImage));
}


ViewerTweedy::~ViewerTweedy()
{
    delete _ui;
}
