#include "ViewerTweedy.h"
#include "ui_ViewerTweedy.h"

#include <tweedy/core/Projet.hpp>

ViewerTweedy::ViewerTweedy(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ViewerTweedy)
{
    _ui->setupUi(this);
    _currentTime = 0;
    _onionAction = new QAction("onion",this);
    //_onionAction->setShortcut(QKeySequence("Space"));
    _onionAction->setStatusTip("Option Onion Skin");
    
    displayChanged(0);
    
    connect(_ui->spinBox, SIGNAL(valueChanged(int)), _onionAction, SLOT(trigger()) );
    connect(_onionAction, SIGNAL(triggered()), this, SLOT(handle_onionAction_triggered()));
    
    //_ui->onionButton->setDefaultAction(_onionAction);
    
}


QToolButton * ViewerTweedy::getPlayPauseButton() { return _ui->playPauseButton; }

QToolButton * ViewerTweedy::getNextButton() { return _ui->nextButton; }

QToolButton * ViewerTweedy::getPreviousButton() { return _ui->previousButton; }

QToolButton * ViewerTweedy::getCaptureButton() { return _ui->captureButton; }

QToolButton * ViewerTweedy::getRetour0Button() { return _ui->retour0Button; }

QLabel * ViewerTweedy::getViewerLabel() { return _ui->viewerLabel; }

QLabel * ViewerTweedy::getTimeLabel() { return _ui->timeLabel; }

QSlider * ViewerTweedy::getTempsSlider() { return _ui->tempsSlider; }


void ViewerTweedy::displayChanged(int time)
{
    _ui->spinBox->setValue(0);
    _currentTime = time;
    Timeline* timeline = &(Projet::getInstance().getTimeline());
    std::string  filename = "img/none.jpg";

    if (time == timeline->maxTime())
        //afficher le temps reel
        filename = "img/realTime.jpg";
    else
        bool isClip = timeline->findCurrentClip(filename,time);

    this->getViewerLabel()->setPixmap(QPixmap(QString::fromStdString(filename)));
   
     
   
    /**/
}



void ViewerTweedy::handle_onionAction_triggered()
{
    int nbFrames = _ui->spinBox->value();
    Timeline t = Projet::getInstance().getTimeline();
    std::string filename = "img/none.jpg";
    int beginTime = _currentTime - nbFrames;
    if (beginTime < 0)
    {
        nbFrames += beginTime;
        beginTime = 0;
    }
    bool found = t.findCurrentClip(filename, beginTime);

    QImage resultImage = QImage(QSize(475,343), QImage::Format_ARGB32_Premultiplied);
    found = resultImage.load(QString::fromStdString(filename));

    /*
    //modification de la transparence ???
    
    for (int i=0; i<resultImage.colorCount(); ++i)
    {
        QColor c(resultImage.color(i));
        c.setAlphaF(0.5);
        resultImage.setColor(i, c.rgba());

    }
    */

    for (int i=1; i<=nbFrames; ++i)
    {
        if (_currentTime - i < 0)
            break;

        found = t.findCurrentClip(filename, beginTime + i);
        QImage destinationImage = QImage(QSize(475,343), QImage::Format_ARGB32_Premultiplied);
        found = destinationImage.load(QString::fromStdString(filename));

        QImage sourceImage(resultImage);

        resultImage = calculateImage(sourceImage, destinationImage);
    }

    this->getViewerLabel()->setPixmap(QPixmap::fromImage(resultImage));
    
}


QImage ViewerTweedy::calculateImage(const QImage& sourceImage, const QImage& destinationImage)
{
    
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

    return resultImage;
}



ViewerTweedy::~ViewerTweedy()
{
    delete _ui;
}
