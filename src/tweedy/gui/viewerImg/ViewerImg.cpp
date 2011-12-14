/*
 * File:   ViewerImg.cpp
 * Author: julien
 * 
 * Created on 13 décembre 2011, 23:05
 */

#include "ViewerImg.h"

ViewerImg::ViewerImg() : ui(new Ui::ViewerImg)

{
    ui->setupUi(this);
}

ViewerImg::~ViewerImg() {
    
    delete ui;
}

