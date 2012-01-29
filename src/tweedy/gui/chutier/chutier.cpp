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
    _tabWidget = new QTabWidget(this);
    _listWidget = new ListWidget(this);
    _importButton = new QToolButton(this);
    _deleteButton = new QToolButton(this);

    //creation des actions
    _importAction = new QAction("Importer",this);
    _deleteAction = new QAction("Supprimer",this);

    //affecter actions aux QToolButton
    _importButton->setDefaultAction(_importAction);
    _deleteButton->setDefaultAction(_deleteAction);

    //creation du widget dockable du viewer
    _viewerChutierDock = new QDockWidget("Visualisation du chutier",this);
    _viewerChutier = new QLabel(_viewerChutierDock);
    _viewerChutier->setBackgroundRole(QPalette::Dark);
    _viewerChutier->setScaledContents(true);
    _viewerChutierDock->setWidget(_viewerChutier);

    _listWidget->setMinimumWidth(250);

    //disposition des widgets
    QHBoxLayout * layoutBoutons = new QHBoxLayout();
    layoutBoutons->addStretch();
    layoutBoutons->addWidget(_importButton);
    layoutBoutons->addWidget(_deleteButton);

    QVBoxLayout * layoutChutier = new QVBoxLayout();
    layoutChutier->addWidget(_listWidget);
    layoutChutier->addLayout(layoutBoutons);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(layoutChutier);
    mainLayout->addWidget(_viewerChutierDock);
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
        QListWidgetItem *item = new QListWidgetItem(QIcon(image), image, _listWidget);
        /*add item to list*/
        _listWidget->addItem(item);
    }


    //image par defaut
    QString defaultImage("img/noPhotoSelected.jpg");
    _viewerChutier->setPixmap(defaultImage);
    _viewerChutier->setScaledContents(true); //centrer l'image dans le QLabel

    connect(_listWidget, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(on_photo_selected(QListWidgetItem*)));
    connect(_importAction, SIGNAL(triggered()), this, SLOT(on_importAction_triggered()));
    connect(_deleteAction, SIGNAL(triggered()), this, SLOT(on_deleteAction_triggered()));
}

void Chutier::on_photo_selected(QListWidgetItem * item)
{
    _viewerChutier->setPixmap(item->text());
}

void Chutier::on_importAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Picture"),QDir::currentPath());

    QListWidgetItem *item = new QListWidgetItem(QIcon(fileName), fileName, _listWidget);

    _listWidget->addItem(item);

    /*add media imported to chutier core*/
    boost::filesystem::path NameOfFileToImport(fileName.toStdString());
    Projet& projectInstance = Projet::getInstance();
    ChutierMediaExt chutierMediaExt = projectInstance.getChutierMediaExt();
    chutierMediaExt.importMediaToChutier(NameOfFileToImport);
    //chutierMediaExt.printMapMediaExt();

}

void Chutier::on_deleteAction_triggered()
{

    QList<QListWidgetItem *> fileSelected= _listWidget->selectedItems();
    if(fileSelected.size())
    {
        for (int i = 0; i < _listWidget->count(); ++i)
        {
            if(_listWidget->item(i)->isSelected())
            {
                QListWidgetItem * item = _listWidget->takeItem(i);
                delete item;
            }
        }
    }

}

void Chutier::contextMenuEvent(QContextMenuEvent *event)
{

    QMenu menu(this);
    menu.addAction(_importAction);
    menu.exec(event->globalPos());

}

Chutier::~Chutier()
{

}
