/*
 * File:   ViewerImg.cpp
 * Author: julien
 * 
 * Created on 13 décembre 2011, 23:05
 */

#include "ViewerImg.h"

ViewerImg::ViewerImg() : QDockWidget(), _labelImg(new QLabel)

{
    setWindowTitle("Visualisation");
    this->setWidget(_labelImg);
    _labelImg->setFixedSize(300, 300);
}

ViewerImg::~ViewerImg() 
{
   delete _labelImg; 
}

