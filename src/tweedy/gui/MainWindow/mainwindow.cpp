#include "mainwindow.h"

#include <tweedy/core/Projet.hpp>

#include <QtGui/QWidget>
#include <QtGui/QDockWidget>
#include <QtGui/QScrollArea>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>
#include <QtGui/QAction>
#include <QtGui/QMenuBar>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QLineEdit>
#include <QtGui/QDesktopWidget>

#include <boost/filesystem.hpp>

#include <iostream>


MainWindow::MainWindow(Projet * projet)
{
    setWindowTitle(tr("TWEEDY - logiciel de stop motion"));

    createActions();
    createStartWindow();
    createMenuBar();
    createToolBar();
    createWidgets();
    createStatusBar();

    _ptrProjet = projet;
    _ptrProjet->setGphotoInstance();

    this->showMaximized();

    std::string filename = "img/none.jpg";
    
    Timeline::UOMapClip clips = timeline->timeline()->mapClip();
    BOOST_FOREACH( const Timeline::UOMapClip::value_type& s, clips )
    {
        if (s.second->timeIn() == 0)
        {
            filename = s.first;
            break;
        }
    }
    
    QPixmap firstPic( QString::fromStdString(filename) );
       
    viewerImg->labelImg()->setPixmap( firstPic );
    
    connect(this->timeline, SIGNAL( displayChanged(std::string) ), this->viewerImg, SLOT(displayImg(std::string)) );

}



/*
  Creer toutes les actions de l'projet
*/
void MainWindow::createActions()
{

    newProjectAction = new QAction(QIcon("img/icones/nouveau.png"),"Nouveau Projet", this);
    newProjectAction->setShortcut(QKeySequence("Ctrl+N"));
    newProjectAction->setStatusTip("Creer un nouveau projet");
    connect(newProjectAction, SIGNAL(triggered()), this, SLOT(on_newProjectAction_triggered()));

    openProjectAction = new QAction(QIcon("img/icones/ouvrir.png"),"Ouvrir",this);
    openProjectAction->setShortcut(QKeySequence("Ctrl+O"));
    openProjectAction->setStatusTip("Ouvrir un projet");

    saveProjectAction = new QAction(QIcon("img/icones/enregistrer.png"),"Enregistrer", this);
    saveProjectAction->setShortcut(QKeySequence("Ctrl+S"));
    saveProjectAction->setStatusTip("Enregistrer votre projet");

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
    
    connect(undoAction, SIGNAL(triggered()), this, SLOT(on_undoButton_clicked()));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(on_redoButton_clicked()));

    _captureAction = new QAction(QIcon("img/icones/capture.png"),"Capture",this);
    _captureAction->setShortcut(QKeySequence("Retour"));
    connect(_captureAction, SIGNAL(triggered()), this,SLOT(on_captureAction_triggered()));

}



void MainWindow::createStartWindow()
{

    //creation fenetre de demarrage
    startWindowDialog = new StartWindow();
    startWindowDialog->setWindowFlags(Qt::WindowStaysOnTopHint);
    startWindowDialog->setModal(false);
    startWindowDialog->show();

    //mettre la fenetre au centre de l'ecran
    const QRect screen = QApplication::desktop()->screenGeometry();
    startWindowDialog->move(screen.center() - startWindowDialog->rect().center());

    startWindowDialog->getNewProjectButton()->setDefaultAction(newProjectAction);
    startWindowDialog->getNewProjectButton()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    startWindowDialog->getNewProjectButton()->setIconSize(QSize(30,30));

    startWindowDialog->getOpenProjectButton()->setDefaultAction(openProjectAction);
    startWindowDialog->getOpenProjectButton()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    startWindowDialog->getOpenProjectButton()->setIconSize(QSize(30,30));

}


/*
  Creer la barre de menu
*/
void MainWindow::createMenuBar()
{

    fileMenu = menuBar()->addMenu(tr("&Fichier"));
    fileMenu->addAction(newProjectAction);
    fileMenu->addAction(openProjectAction);
    menuBar()->addSeparator();
    fileMenu->addAction(saveProjectAction);
    fileMenu->addAction(quitAction);

    editMenu = menuBar()->addMenu(tr("&Edition"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    viewMenu = menuBar()->addMenu(tr("Affichage"));

    timelineMenu = menuBar()->addMenu(tr("Timeline"));

    paramsMenu = menuBar()->addMenu(tr("Configuration"));

    helpMenu = menuBar()->addMenu(tr("Aide"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

}


/*
    Creer la barre d'outils
*/
void MainWindow::createToolBar()
{

    fileToolBar = addToolBar("File");
    fileToolBar->addAction(newProjectAction);
    fileToolBar->addAction(saveProjectAction);
    fileToolBar->addAction(quitAction);

    editToolBar = addToolBar("Edit");
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);

}


/*
  Creer tous les widgets
*/
void MainWindow::createWidgets()
{
    //Dock Chutier

    QDockWidget * chutierDock = new QDockWidget(this);
    chutier = new Chutier();
    chutierDock->setWidget(chutier);
    addDockWidget(Qt::TopDockWidgetArea, chutierDock);
    viewMenu->addAction(chutier->viewerChutierDock->toggleViewAction());

    createWidgetViewer();

    //Dock Timeline

    timeline = new TimeLineUi();
    timeline->resize(QSize(this->width(), 300));
    addDockWidget(Qt::BottomDockWidgetArea, timeline);
    
}


void MainWindow::createWidgetViewer()
{

    QDockWidget * contentViewerDock = new QDockWidget("Viewer",this);
    viewerImg = new ViewerImg();
    contentViewerDock->setWidget(viewerImg);
    addDockWidget(Qt::TopDockWidgetArea, contentViewerDock);
    viewMenu->addAction(contentViewerDock->toggleViewAction());
    
    viewerImg->_capture->setDefaultAction(_captureAction);
    viewerImg->_capture->setIconSize(QSize(40,40));

}


void MainWindow::on_captureAction_triggered()
{
    int isConnected = _ptrProjet->tryToConnectCamera();
    std::cout<<"IS CONNECTED"<<isConnected<<std::endl;
    if (isConnected == 0)
    {

        QMessageBox::about(this, tr("Warning"),
                            tr("No camera connected to the computer"));
        std::cout<<"No camera connected to the computer"<<std::endl;
    }
    else
    {
	std::cout<<"Camera connected"<<std::endl;
        _ptrProjet->setFolderToSavePictures();
        //gPhotoInstance->captureToFile();
    }

}

void MainWindow::on_newProjectAction_triggered()
{
    newProjectDialog = new newProjectWindow();
    newProjectDialog->show();
    startWindowDialog->hide();

    connect(newProjectDialog->getSearchFolderProjectButton(),SIGNAL(clicked()), this, SLOT(on_searchFolderProjectButton_clicked()));
}

void MainWindow::on_searchFolderProjectButton_clicked()
{
    QFileDialog * fileDialog = new QFileDialog();
    QString fileName =fileDialog->getExistingDirectory(this,
                                                    tr("Choisir l'emplacement du projet"),
                                                    QString(boost::filesystem::initial_path().string().c_str()));

    newProjectDialog->getFolderProjectLineEdit()->setText(fileName);
    newProjectDialog->show();

}


void MainWindow::on_undoButton_clicked(){
    
    CommandManager& cmdMng = (Projet::getInstance())->getCommandManager();
    if(cmdMng.canUndo()){
        cmdMng.undo();
        timeline->updateTable();
    }
}

void MainWindow::on_redoButton_clicked(){
    
    CommandManager& cmdMng = (Projet::getInstance())->getCommandManager();
    if(cmdMng.canRedo()){
        cmdMng.redo();
        timeline->updateTable();
    }
}


/*
  Creer la barre de statut
*/
void MainWindow::createStatusBar()
{

    myStatusBar = statusBar();
    //'Pret' par défaut
    myStatusBar->showMessage("Pret");

}


MainWindow::~MainWindow()
{

    delete chutier;
    delete viewerImg;
    delete timeline;
    delete startWindowDialog;
    _ptrProjet->kill ();
    //gPhotoInstance->kill ();

}
