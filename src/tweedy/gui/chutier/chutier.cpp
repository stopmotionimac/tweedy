#include "chutier.h"
#include "ui_chutier.h"

#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>

Chutier::Chutier(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chutier)
{
    ui->setupUi(this);

    QString image1("img/tweedy0.jpg");
    QString image2("img/tweedy1.jpg");
    QString image3("img/tweedy2.jpg");

    listWidget = new QListWidget(ui->capture);

    QListWidgetItem *item = new QListWidgetItem(QIcon(image1), image1, listWidget);
    QListWidgetItem *item2 = new QListWidgetItem(QIcon(image2),image2, listWidget);
    QListWidgetItem *item3 = new QListWidgetItem(QIcon(image3),image3, listWidget);
    listWidget->addItem(item);
    listWidget->addItem(item2);
    listWidget->addItem(item3);

    ui->viewer->setBackgroundRole(QPalette::Dark);
    ui->viewer->adjustSize();

    connect(listWidget, SIGNAL(itemActivated(QListWidgetItem*)),this, SLOT(on_photo_selected(QListWidgetItem*)));

}

void Chutier::on_photo_selected(QListWidgetItem * item) {

    ui->viewer->setPixmap(item->text());

}


Chutier::~Chutier()
{
    delete ui;
}
