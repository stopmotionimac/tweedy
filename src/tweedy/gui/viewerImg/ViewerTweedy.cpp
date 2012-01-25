#include "viewertweedy.h"
#include "ui_viewertweedy.h"

ViewerTweedy::ViewerTweedy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewerTweedy)
{
    ui->setupUi(this);
}

ViewerTweedy::~ViewerTweedy()
{
    delete ui;
}
