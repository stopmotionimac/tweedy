#include <QtGui/QPushButton>

#include "ViewerImg.h"


ViewerImg::ViewerImg() : QWidget(), _labelImg(new QLabel(this))

{
    setWindowTitle("Visualisation");
    _labelImg->setScaledContents(true);
    _capture = new QToolButton(this);
    /*_playButton = new QToolButton(this);
    _nextButton = new QToolButton(this);
    _previousButton = new QToolButton(this);
    _pauseButton = new QToolButton(this);*/

    /*QHBoxLayout * layoutPlayer = new QHBoxLayout(this);
    layoutPlayer->addStretch();

    QGridLayout * layoutGrid = new QGridLayout(this);
    layoutGrid->addWidget(_capture, 0, 0, 3, 3);
    layoutGrid->addLayout(layoutPlayer);*/


    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->addWidget(_labelImg);
    layout->addWidget(_capture);
    setLayout(layout);

}

void ViewerImg::displayImg(std::string filename)
{
    _labelImg->setPixmap( QString::fromStdString(filename) );
    
}  


ViewerImg::~ViewerImg() 
{
    delete _labelImg;
    delete _capture;
}
