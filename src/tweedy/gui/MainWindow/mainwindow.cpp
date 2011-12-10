#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QWidget>
#include <QtGui/QScrollArea>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap *pixmap_img = new QPixmap("/images/example.jpg");

    QLabel *imageLabel = new QLabel;
    ui->viewer->setBackgroundRole(QPalette::Dark);
    ui->viewer->setWidget(imageLabel);


    imageLabel->setPixmap(*pixmap_img);
    imageLabel->adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}
