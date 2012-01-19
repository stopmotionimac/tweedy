/*
 * File:   ViewerImg.cpp
 * Author: julien
 * 
 * Created on 13 décembre 2011, 23:05
 */

#include <QtGui/QPushButton>

#include "ViewerImg.h"


ViewerImg::ViewerImg() : QWidget(), _labelImg(new QLabel(this))

{
    setWindowTitle("Visualisation");

    _capture = new QPushButton("Capture",this);

    QVBoxLayout * layout = new QVBoxLayout();
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

