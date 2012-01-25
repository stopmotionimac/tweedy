#include <QtGui/QPushButton>

#include "ViewerImg.h"



ViewerImg::ViewerImg( QWidget* parent ) : QWidget(parent), _labelImg(new QLabel(this)), _qGlViewer(new GlWidgetViewer(this))
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
    //layoutWidget->addWidget(_labelImg);
    layoutWidget->addWidget(_qGlViewer);
    
    layoutWidget->addWidget(_capture);
    setLayout(layoutWidget);

}

void ViewerImg::displayImg(std::string filename)
{
   _qGlViewer->setImgtoDisplay(QImage(QString::fromStdString(filename)));
   _qGlViewer->paintGL();
   _labelImg->setPixmap(QPixmap(QString::fromStdString(filename)));
}  


ViewerImg::~ViewerImg() 
{
    delete _labelImg;
    delete _capture;
}
