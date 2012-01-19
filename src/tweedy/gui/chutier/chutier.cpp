#include "chutier.h"

#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QSplitter>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QFileDialog>
#include <QtCore/QDir>

#include <iostream>

Chutier::Chutier(QWidget *parent) :
    QWidget(parent)
{

    listWidget = new ListWidget(this);
    importButton = new QPushButton("Import",this);
    deleteButton = new QPushButton("Delete",this);

    viewerChutier = new QLabel(this);
    viewerChutier->setBackgroundRole(QPalette::Dark);
    viewerChutier->setFixedSize(300, 200);


    QGridLayout * leftLayout = new QGridLayout();
    leftLayout->addWidget(listWidget, 0, 0, 1, 2);
    leftLayout->addWidget(importButton, 1, 0);
    leftLayout->addWidget(deleteButton, 1, 1);

    QVBoxLayout * rightLayout = new QVBoxLayout();
    rightLayout->addWidget(viewerChutier);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    /*liste des chemins -- a changer plus tard*/
    QString image1("img/tweedy0.jpg");
    QString image2("img/tweedy1.jpg");
    QString image3("img/tweedy2.jpg");

    /*liste des items*/
    QListWidgetItem *item = new QListWidgetItem(QIcon(image1), image1, listWidget);
    QListWidgetItem *item2 = new QListWidgetItem(QIcon(image2),image2, listWidget);
    QListWidgetItem *item3 = new QListWidgetItem(QIcon(image3),image3, listWidget);

    /*ajout des items*/
    listWidget->addItem(item);
    listWidget->addItem(item2);
    listWidget->addItem(item3);

    connect(listWidget, SIGNAL(itemActivated(QListWidgetItem*)),this, SLOT(on_photo_selected(QListWidgetItem*)));
    connect(importButton, SIGNAL(clicked()), this, SLOT(on_importButton_clicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(on_deleteButton_clicked()));
}

void Chutier::on_photo_selected(QListWidgetItem * item)
{
    viewerChutier->setPixmap(item->text());
}

void Chutier::on_importButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Picture"),QDir::currentPath());

    QListWidgetItem *item = new QListWidgetItem(QIcon(fileName), fileName, listWidget);

    listWidget->addItem(item);

}

void Chutier::on_deleteButton_clicked(){

    QList<QListWidgetItem *> fileSelected= listWidget->selectedItems();
    if(fileSelected.size())
    {
        for (int i = 0; i < listWidget->count(); ++i)
        {
            if(listWidget->item(i)->isSelected())
            {
                QListWidgetItem * item = listWidget->takeItem(i);
                delete item;
            }
        }
    }

}

Chutier::~Chutier()
{

}
