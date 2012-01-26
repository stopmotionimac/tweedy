#include "ViewerTweedy.h"
#include "ui_ViewerTweedy.h"

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

ViewerTweedy::~ViewerTweedy()
{
    delete _ui;
}
