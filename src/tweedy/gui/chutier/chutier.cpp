#include "chutier.h"

#include <QtGui/QGridLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QSplitter>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QFileDialog>
#include <QtGui/QMenu>

#include <iostream>

Chutier::Chutier(QWidget *parent) :
    QWidget(parent)
{

    //creation des widgets
    listWidget = new ListWidget(this);
    listWidget->setMaximumSize(this->width()/2,this->height());
    importButton = new QToolButton(this);
    deleteButton = new QToolButton(this);

    //creation des actions
    importAction = new QAction("Importer",this);
    deleteAction = new QAction("Supprimer",this);

    //affecter actions aux QToolButton
    importButton->setDefaultAction(importAction);
    deleteButton->setDefaultAction(deleteAction);

    viewerChutier = new QLabel(this);
    viewerChutier->setBackgroundRole(QPalette::Dark);
    viewerChutier->setFixedSize(this->width()/2, this->height()/2);

    //creation du widget dockable du viewer
    viewerChutierDock = new QDockWidget("Visualisation du chutier",this);
    viewerChutierDock->setWidget(viewerChutier);

    //disposition des widgets
    QGridLayout * leftLayout = new QGridLayout();
    leftLayout->addWidget(listWidget, 0, 0, 1, 2);
    leftLayout->addWidget(importButton, 1, 0);
    leftLayout->addWidget(deleteButton, 1, 1);

    QVBoxLayout * rightLayout = new QVBoxLayout();
    rightLayout->addWidget(viewerChutierDock);
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

    //image par defaut
    QString defaultImage("img/noPhotoSelected.jpg");
    viewerChutier->setPixmap(defaultImage);
    viewerChutier->setScaledContents(true); //centrer l'image dans le QLabel

    connect(listWidget, SIGNAL(itemActivated(QListWidgetItem*)),this, SLOT(on_photo_selected(QListWidgetItem*)));
    connect(importAction, SIGNAL(triggered()), this, SLOT(on_importAction_triggered()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(on_deleteAction_triggered()));
}

void Chutier::on_photo_selected(QListWidgetItem * item)
{
    viewerChutier->setPixmap(item->text());
}

void Chutier::on_importAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Picture"),QDir::currentPath());

    QListWidgetItem *item = new QListWidgetItem(QIcon(fileName), fileName, listWidget);

    listWidget->addItem(item);

}

void Chutier::on_deleteAction_triggered()
{

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

void Chutier::contextMenuEvent(QContextMenuEvent *event)
{

    QMenu menu(this);
    menu.addAction(importAction);
    menu.exec(event->globalPos());

}

Chutier::~Chutier()
{

}
