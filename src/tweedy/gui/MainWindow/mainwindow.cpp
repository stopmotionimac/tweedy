#include "mainwindow.h"

#include <QtGui/QWidget>
#include <QtGui/QDockWidget>
#include <QtGui/QScrollArea>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtGui/QAction>
#include <QtGui/QMenuBar>
#include <QtCore/QFile>



MainWindow::MainWindow()
{
    setWindowTitle(tr("TWEEDY - logiciel de stop motion"));

    createActions();
    createMenuBar();
    createToolBar();
    createWidgets();
    createStatusBar();

    resize(900,700);
    
    
    if ( (*timeline->clips().begin()).timeIn() == 0 )
        viewerImg->labelImg()->setPixmap( QPixmap( QString::fromStdString((*timeline->clips().begin()).imgPath().string()) ) );
    else    
        viewerImg->labelImg()->setPixmap( QPixmap("img/none.jpg") );
    
    connect(this->timeline, SIGNAL( displayChanged(unsigned int, listC) ), this->viewerImg, SLOT(displayImg(unsigned int, listC)) );

}

void MainWindow::createActions(){

    newAction = new QAction(QIcon("img/icones/nouveau.png"),"Nouveau Projet", this);
    newAction->setShortcut(QKeySequence("Ctrl+N"));
    newAction->setStatusTip("Creer un nouveau projet");

    openAction = new QAction(QIcon("img/icones/ouvrir.png"),"Ouvrir",this);
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    openAction->setStatusTip("Ouvrir un projet");

    saveAction = new QAction(QIcon("img/icones/enregistrer.png"),"Enregistrer", this);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    saveAction->setStatusTip("Enregistrer votre projet");

    quitAction = new QAction(QIcon("img/icones/quitter.png"),"&Quitter", this);
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    quitAction->setStatusTip("Quitter Tweedy");
    connect(quitAction, SIGNAL(triggered()), qApp,SLOT(quit()));

    undoAction = new QAction(QIcon("img/icones/undo.png"),"Undo",this);
    undoAction->setShortcut(QKeySequence("Ctrl+Z"));

    redoAction = new QAction(QIcon("img/icones/redo.png"),"Redo",this);
    redoAction->setShortcut(QKeySequence("Shift+Ctrl+Z"));

    aboutAction = new QAction("A propos de Tweedy",this);

    aboutQtAction = new QAction("A propos de Qt",this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void MainWindow::createMenuBar(){

    fileMenu = menuBar()->addMenu(tr("&Fichier"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    menuBar()->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(quitAction);

    editMenu = menuBar()->addMenu(tr("&Edition"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    viewMenu = menuBar()->addMenu(tr("Affichage"));

    timelineMenu = menuBar()->addMenu(tr("Timeline"));

    helpMenu = menuBar()->addMenu(tr("Aide"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

}

void MainWindow::createToolBar(){

    fileToolBar = addToolBar("File");
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(quitAction);

    editToolBar = addToolBar("Edit");
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);

}

void MainWindow::createWidgets(){

    QDockWidget * chutierDock = new QDockWidget(this);
    chutier = new Chutier();
    chutierDock->setWidget(chutier);
    addDockWidget(Qt::TopDockWidgetArea, chutierDock);

    //ajout du viewer
    QDockWidget * contentViewerDock = new QDockWidget(this);	
    viewerImg = new ViewerImg();
    viewerImg->setFixedSize(400, 300);
    contentViewerDock->setWidget(viewerImg);
    addDockWidget(Qt::TopDockWidgetArea, contentViewerDock);
    
    //ajout de la timeline a la mainwindow
    timeline = new TimeLine();
    //timeline->setFixedSize(670, 300);
    addDockWidget(Qt::BottomDockWidgetArea, timeline);
}

void MainWindow::createStatusBar(){

    myStatusBar = statusBar();
    myStatusBar->showMessage("Pret");

}

MainWindow::~MainWindow(){

    delete chutier;
    delete viewerImg;
    delete timesheet;

}

