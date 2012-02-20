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
    _listWidgetCapture = new ListWidget(this);
    _listWidgetImport = new ListWidget(this);
    _importButton = new QToolButton(this);
    _deleteButton = new QToolButton(this);

    _tabWidget->addTab(_listWidgetImport,QIcon("img/icones/import.png"),"Imported");
    _tabWidget->addTab(_listWidgetCapture,QIcon("img/icones/capture.png"),"Captured");

    //creation des actions
    _importAction = new QAction(QIcon("img/icones/import.png"),"Import",this);
    _deleteAction = new QAction(QIcon("img/icones/delete.png"),"Delete",this);

    //affecter actions aux QToolButton
    _importButton->setDefaultAction(_importAction);
    _deleteButton->setDefaultAction(_deleteAction);
    _importButton->setIconSize(QSize(25,25));
    _importButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    _deleteButton->setIconSize(QSize(25,25));
    _deleteButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //creation du widget dockable du viewer
    _viewerChutierDock = new QDockWidget("Media List Viewer",this);
    _viewerChutier = new QLabel(_viewerChutierDock);
    _viewerChutier->setBackgroundRole(QPalette::Dark);
    _viewerChutier->setScaledContents(false);
    _viewerChutierDock->setWidget(_viewerChutier);
    _viewerChutier->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _tabWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    //en dur ??????
    _viewerChutier->setMaximumSize(600,400);

    //disposition des widgets
    QHBoxLayout * layoutBoutons = new QHBoxLayout();
    layoutBoutons->addStretch();
    layoutBoutons->addWidget(_importButton);
    layoutBoutons->addWidget(_deleteButton);

    QVBoxLayout * layoutChutier = new QVBoxLayout();
    layoutChutier->addWidget(_tabWidget);
    layoutChutier->addLayout(layoutBoutons);

    QSplitter* splitter = new QSplitter(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(layoutChutier);
    //mainLayout->addWidget(splitter);
    mainLayout->addWidget(_viewerChutierDock);
    setLayout(mainLayout);


    Projet& projectInstance = Projet::getInstance();

    /*full chutier to have exemple => no need if save!*/
    ChutierMediaExt chutierMediaExt = projectInstance.getChutierMediaExt();
    //boost::filesystem::path pathMediaToAdd("projet/mediasExt/tweedy3.jpg");
    //boost::filesystem::path pathMediaToAdd2("projet/mediasExt/tweedy2.jpg");
    /*to add media ext to chutier*/
    //chutierMediaExt.importMediaToChutier(pathMediaToAdd);
    //chutierMediaExt.importMediaToChutier(pathMediaToAdd2);
    //chutierMediaExt.printMapMediaExt();

    boost::ptr_unordered_map<std::string, MediaExt>::iterator iter;       

    /*to add media ext to chutier media ext*/
   for (iter = chutierMediaExt.getMapMediaExt().begin(); iter != chutierMediaExt.getMapMediaExt().end(); ++iter)
    {
        std::cout<<iter->first<<std::endl;
        /*path*/
        QString image(iter->first.data());
        /*item*/
        QListWidgetItem *item = new QListWidgetItem(QIcon(image), image, _listWidgetImport);
        /*add item to list*/
        _listWidgetImport->addItem(item);
    }

   /*to add media to chutier photo*/


    //image par defaut
    QString defaultImage("img/noPhotoSelected.jpg");
    _viewerChutier->setPixmap(defaultImage);

    connect(_listWidgetImport, SIGNAL(itemSelectionChanged()),this, SLOT(on_photo_selected_import()));
    connect(_listWidgetCapture, SIGNAL(itemSelectionChanged()),this, SLOT(on_photo_selected_capture()));
    connect(_importAction, SIGNAL(triggered()), this, SLOT(on_importAction_triggered()));
    connect(_deleteAction, SIGNAL(triggered()), this, SLOT(on_deleteAction_triggered()));
}

void Chutier::on_photo_selected_import()
{
    QPixmap pixmap(_listWidgetImport->currentItem()->text());
    pixmap.scaled(_viewerChutier->width(),_viewerChutier->height(),Qt::KeepAspectRatioByExpanding);
    _viewerChutier->setPixmap(pixmap);

}

void Chutier::on_photo_selected_capture()
{
    QPixmap pixmap(_listWidgetCapture->currentItem()->text());
    pixmap.scaled(_viewerChutier->width(),_viewerChutier->height(),Qt::KeepAspectRatioByExpanding);
    _viewerChutier->setPixmap(pixmap);

}

void Chutier::on_importAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Picture"),QDir::currentPath());

    QListWidgetItem *item = new QListWidgetItem(QIcon(fileName), fileName, _listWidgetImport);

    _listWidgetImport->addItem(item);

    _tabWidget->setCurrentWidget(_listWidgetImport);

    /*add media imported to chutier core*/
    boost::filesystem::path NameOfFileToImport(fileName.toStdString());
    Projet& projectInstance = Projet::getInstance();
    ChutierMediaExt chutierMediaExt = projectInstance.getChutierMediaExt();
    chutierMediaExt.importMediaToChutier(NameOfFileToImport);
    //chutierMediaExt.printMapMediaExt();

}

void Chutier::on_deleteAction_triggered()
{
    //bug quand on supprime tout
    QList<QListWidgetItem *> fileSelected= _listWidgetImport->selectedItems();
    for (int i = 0; i < fileSelected.count(); ++i)
    {
        if(_listWidgetImport->count() != 0) {
            QListWidgetItem * item = _listWidgetImport->takeItem(i);
            delete item;
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
