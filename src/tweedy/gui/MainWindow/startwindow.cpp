#include "startwindow.h"
#include "ui_startwindow.h"

#include <iostream>

StartWindow::StartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("TWEEDY - logiciel de stop motion"));

}


QToolButton* StartWindow::getNewProjectButton()
{
    return ui->newProjectButton;
}

QToolButton* StartWindow::getOpenProjectButton()
{
    return ui->openProjectButton;
}

StartWindow::~StartWindow()
{
    delete ui;
}
