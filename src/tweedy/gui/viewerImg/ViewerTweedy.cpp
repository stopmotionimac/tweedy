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

QToolButton * ViewerTweedy::getRetour0Button() { return _ui->retour0Button; }

QLabel * ViewerTweedy::getViewerLabel() { return _ui->viewerLabel; }

QLabel * ViewerTweedy::getTimeLabel() { return _ui->timeLabel; }


void ViewerTweedy::displayChanged(int time)
{
    Timeline* timeline = &(Projet::getInstance().getTimeline());
    std::string  filename = "img/none.jpg";

    if (time == timeline->maxTime())
        //afficher le temps reel
        filename = "img/realTime.jpg";
    else
        bool isClip = timeline->findCurrentClip(filename,time);

    this->getViewerLabel()->setPixmap(QPixmap(QString::fromStdString(filename)));
}


ViewerTweedy::~ViewerTweedy()
{
    delete _ui;
}
