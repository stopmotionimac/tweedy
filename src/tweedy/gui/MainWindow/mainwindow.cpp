#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "styleTweedy.css"

#include "ui_mainwindow.h"

#include <QtGui/QWidget>
#include <QtGui/QScrollArea>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtCore/QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLatin1String cssContent( QFile("styleTweedy.css").readAll() );
    this->setStyleSheet(cssContent);

    //QDir * currentDir = new QDir("img/");

    QString image1("img/tweedy0.jpg");
    QString image2("img/tweedy1.jpg");
    QString image3("img/tweedy2.jpg");

    listWidget = new QListWidget(ui->photos);

    QListWidgetItem *item = new QListWidgetItem(QIcon(image1), image1, listWidget);
    QListWidgetItem *item2 = new QListWidgetItem(QIcon(image2),image2, listWidget);
    QListWidgetItem *item3 = new QListWidgetItem(QIcon(image3),image3, listWidget);
    listWidget->addItem(item);
    listWidget->addItem(item2);
    listWidget->addItem(item3);

    QPixmap *pixmap_img = new QPixmap("/images/example.jpg");

    imageLabel = new QLabel;

    ui->viewer->setBackgroundRole(QPalette::Dark);
    ui->viewer->setWidget(imageLabel);


    //imageLabel->setPixmap(image1);
    imageLabel->adjustSize();

  
    viewerImg = new ViewerImg();
    //ajout de viewerImg a la mainwindow
    addDockWidget(Qt::RightDockWidgetArea, viewerImg);
    
     timesheet = new TimeSheet(viewerImg);
    //ajout de timesheet a la mainwindow
    addDockWidget(Qt::BottomDockWidgetArea, timesheet);

    connect(listWidget, SIGNAL(itemActivated(QListWidgetItem*)),this, SLOT(on_photo_selected(QListWidgetItem*)));
}

void MainWindow::on_photo_selected(QListWidgetItem * item) {

    imageLabel->setPixmap(item->text());
    ui->viewer->setWidget(imageLabel);
}


MainWindow::~MainWindow()
{
    delete ui;
}
