#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QWidget>
#include <QtGui/QScrollArea>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString * image1 = new QString("example.jpg");
    QString * image2 = new QString("full.jpg");

    /*QListWidgetItem *item = new QListWidgetItem(QIcon(*image1), *image1, ui->listWidget);
    QListWidgetItem *item2 = new QListWidgetItem(QIcon(*image2),*image2, ui->listWidget);
    ui->listWidget->addItem(item);
    ui->listWidget->addItem(item2);*/

    imageLabel = new QLabel;
    ui->viewer->setBackgroundRole(QPalette::Dark);
    ui->viewer->setWidget(imageLabel);

    imageLabel->setPixmap(*image1);
    imageLabel->adjustSize();

    //connect(ui->listWidget, SIGNAL(itemActivated(QListWidgetItem*)),this, SLOT(on_photo_selected(QListWidgetItem*)));
}

void MainWindow::on_photo_selected(QListWidgetItem * item) {

    imageLabel->setPixmap(item->text());
    ui->viewer->setWidget(imageLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
