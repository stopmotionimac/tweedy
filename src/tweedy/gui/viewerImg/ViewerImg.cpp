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

void ViewerImg::displayImg(unsigned int newValue, listC clips)
{
    //if (newValue == -1)
      //  _labelImg->setPixmap( QPixmap( QString::fromStdString("img/none.jpg") ) );
    
    //else
    //{
        for (It it=clips.begin(); it!=clips.end(); ++it)
        {
            if ( (*it).timeIn() <= newValue && (*it).timeOut() > newValue )
            {
                _labelImg->setPixmap( QPixmap( QString::fromStdString( (*it).imgPath().string() ) ) );
                break;
            }
        }
    //}

}  


ViewerImg::~ViewerImg() 
{
    delete _labelImg;
    delete _capture;
}

