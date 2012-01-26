#include "chutier.h"

#include <tweedy/core/Projet.hpp>
#include <tweedy/core/ChutierMediaExt.hpp>
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


    Projet& projectInstance = Projet::getInstance();

    /*full chutier to have exemple => no need if save!*/
    ChutierMediaExt chutierMediaExt = projectInstance.getChutierMediaExt();
    boost::filesystem::path pathMediaToAdd("projet/mediasExt/tweedy3.jpg");
    boost::filesystem::path pathMediaToAdd2("projet/mediasExt/tweedy2.jpg");
    /*to add media ext to chutier*/
    chutierMediaExt.importMediaToChutier(pathMediaToAdd);
    chutierMediaExt.importMediaToChutier(pathMediaToAdd2);
    //chutierMediaExt.printMapMediaExt();
            
    boost::ptr_unordered_map<std::string, MediaExt>::iterator iter;       

    /*to add media ext to chutier*/
   for (iter = chutierMediaExt.getMapMediaExt().begin(); iter != chutierMediaExt.getMapMediaExt().end(); ++iter)
    {
        std::cout<<iter->first<<std::endl;
        /*path*/
        QString image(iter->first.data());
        /*item*/
        QListWidgetItem *item = new QListWidgetItem(QIcon(image), image, listWidget);
        /*add item to list*/
        listWidget->addItem(item);
    }


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
