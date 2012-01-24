#include "mainwindow.h"

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
#include <QtCore/QDir>
#include <QtCore/QFile>

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

    gPhotoInstance = Gphoto::getInstance ();

    resize(900,700);
    
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
void MainWindow::createActions(){

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

}



void MainWindow::createStartWindow()
{

    //creation fenetre de demarrage
    startWindowDialog = new StartWindow();
    startWindowDialog->setWindowFlags(Qt::WindowStaysOnTopHint);
    startWindowDialog->show();

    startWindowDialog->getNewProjectButton()->setDefaultAction(newProjectAction);
    startWindowDialog->getNewProjectButton()->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    startWindowDialog->getOpenProjectButton()->setDefaultAction(openProjectAction);
    startWindowDialog->getOpenProjectButton()->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

}


/*
  Creer la barre de menu
*/
void MainWindow::createMenuBar(){

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
void MainWindow::createToolBar(){

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
void MainWindow::createWidgets(){

    //Dock Chutier

    QDockWidget * chutierDock = new QDockWidget(this);
    chutier = new Chutier();
    chutierDock->setWidget(chutier);
    addDockWidget(Qt::TopDockWidgetArea, chutierDock);
    viewMenu->addAction(chutier->viewerChutierDock->toggleViewAction());


    createWidgetViewer();


    //Dock Timeline

    timeline = new TimeLineUi();
    addDockWidget(Qt::BottomDockWidgetArea, timeline);
    
}


void MainWindow::createWidgetViewer()
{

    QDockWidget * contentViewerDock = new QDockWidget("Viewer",this);
    viewerImg = new ViewerImg();
    viewerImg->setFixedSize(400, 300);
    contentViewerDock->setWidget(viewerImg);
    addDockWidget(Qt::TopDockWidgetArea, contentViewerDock);
    viewMenu->addAction(contentViewerDock->toggleViewAction());
    
    _captureAction = new QAction("Capture",this);
    _captureAction->setShortcut(QKeySequence("Retour"));
    viewerImg->_capture->setDefaultAction(_captureAction);
    connect(_captureAction, SIGNAL(triggered()), this,SLOT(on_captureAction_triggered()));
}


void MainWindow::on_captureAction_triggered()
{
    int isConnected = gPhotoInstance->tryToConnectCamera();
    if (isConnected == 0)
    {

        QMessageBox::about(this, tr("Warning"),
                            tr("No camera connected to the computer"));
        std::cout<<"No camera connected to the computer"<<std::endl;
    }
    else
    {
        gPhotoInstance->setFolderToSavePictures();
        gPhotoInstance->captureToFile();
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choisir l'emplacement du projet"),QDir::currentPath());

    //QString fileName = QFileDialog::getOpenFileName(this,tr("Choisir l'emplacement du projet"),boost::filesystem::initial_path());

    newProjectDialog->getFolderProjectLineEdit()->setText(fileName);

}

/*
  Creer la barre de statut
*/
void MainWindow::createStatusBar(){

    myStatusBar = statusBar();
    //'Pret' par défaut
    myStatusBar->showMessage("Pret");

}


MainWindow::~MainWindow(){

    delete chutier;
    delete viewerImg;
    delete timeline;
    delete startWindowDialog;
    gPhotoInstance->kill ();

}
