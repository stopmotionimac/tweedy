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

}

AboutTweedy::~AboutTweedy()
{
    delete _ui;
}
