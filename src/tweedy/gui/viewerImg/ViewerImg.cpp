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

void ViewerImg::displayImg(unsigned int newValue, listC clips)
{
    _labelImg->setPixmap( QPixmap("img/none.jpg") );
    for (It it=clips.begin(); it!=clips.end(); ++it)
    {
        if ( (*it).timeIn() <= newValue && (*it).timeOut() > newValue )
        {
            _labelImg->setPixmap( QPixmap((*it).imgPath()) );
            break;
        }
    }

}  


ViewerImg::~ViewerImg() 
{
   delete _labelImg; 
}

