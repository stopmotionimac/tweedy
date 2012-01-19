/*
 * File:   ViewerImg.cpp
 * Author: julien
 * 
 * Created on 13 décembre 2011, 23:05
 */

#include "ViewerImg.h"


ViewerImg::ViewerImg() : QWidget(), _labelImg(new QLabel(this))

{
    setWindowTitle("Visualisation");
    _labelImg->setFixedSize(300, 300);
}

void ViewerImg::displayImg(std::string filename)
{
    _labelImg->setPixmap( QString::fromStdString(filename) );
    
}  


ViewerImg::~ViewerImg() 
{
   delete _labelImg; 
}

