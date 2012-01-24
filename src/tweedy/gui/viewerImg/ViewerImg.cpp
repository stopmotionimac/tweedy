#include <QtGui/QPushButton>

#include "ViewerImg.h"


ViewerImg::ViewerImg() : QWidget(), _labelImg(new QLabel(this))

{
    setWindowTitle("Visualisation");
    _labelImg->setScaledContents(true);
    _capture = new QToolButton(this);

    //QGridLayout * layoutGrid = new QGridLayout(this);
    //layoutGrid->addWidget(_capture);

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
