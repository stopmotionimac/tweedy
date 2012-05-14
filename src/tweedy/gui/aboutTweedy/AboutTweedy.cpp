#include "AboutTweedy.hpp"
#include "ui_AboutTweedy.h"

#include <QtGui/QPixmap>

AboutTweedy::AboutTweedy(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::AboutTweedy)
{
    _ui->setupUi(this);
    _ui->logoTWEEDYLabel->setPixmap(QString::fromStdString("img/logo.png"));
    _ui->logoIMACLabel->setPixmap(QString::fromStdString("img/imac.jpg"));
    QPixmap team = QString::fromStdString("img/lateam.JPG");
    _ui->photoLabel->setPixmap(team.scaled(450,300));
    _ui->photoLabel->setFixedSize(450,300);
    _ui->photoLabel->setAlignment (Qt::AlignCenter);
    this->setFixedSize(470,580);
}

AboutTweedy::~AboutTweedy()
{
    delete _ui;
}
