#include "viewertweedy.h"
#include "ui_viewertweedy.h"

ViewerTweedy::ViewerTweedy(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ViewerTweedy)
{
    _ui->setupUi(this);
}


QToolButton * ViewerTweedy::getPlayPauseButton()
{
    return _ui->playPauseButton;
}

QToolButton * ViewerTweedy::getNextButton()
{
    return _ui->nextButton;
}

QToolButton * ViewerTweedy::getPreviousButton()
{
    return _ui->previousButton;
}

QToolButton * ViewerTweedy::getCaptureButton()
{
    return _ui->captureButton;
}


ViewerTweedy::~ViewerTweedy()
{
    delete _ui;
}