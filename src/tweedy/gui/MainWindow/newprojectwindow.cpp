#include "newprojectwindow.h"
#include "ui_newprojectwindow.h"

newProjectWindow::newProjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newProjectWindow)
{
    ui->setupUi(this);
}

newProjectWindow::~newProjectWindow()
{
    delete ui;
}
