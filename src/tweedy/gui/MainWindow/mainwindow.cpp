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

#include <tweedy/core/command/GroupeUndoRedoCmd.hpp>
#include <tweedy/core/command/clip/CmdClipSetTimeRange.hpp>

#include <boost/filesystem.hpp>

#include <tweedy/core/action/ActCapturePicture.hpp>

#include <iostream>


MainWindow::MainWindow()
{
    setWindowTitle(tr("TWEEDY - logiciel de stop motion"));

    createActions();
    createStartWindow();
    createMenuBar();
    createToolBar();
    createWidgets();
    createStatusBar();

    Projet& projectInstance = project();

    this->showMaximized();

    connect(this->timeline, SIGNAL( timeChanged(int) ), this->viewerImg, SLOT(displayChanged(int)) );

}



/*
  Creer toutes les actions de l'projet
*/
void MainWindow::createActions()
{

    newProjectAction = new QAction(QIcon("img/icones/new1.png"),"Nouveau Projet", this);
    newProjectAction->setShortcut(QKeySequence("Ctrl+N"));
    newProjectAction->setStatusTip("Creer un nouveau projet");
    connect(newProjectAction, SIGNAL(triggered()), this, SLOT(on_newProjectAction_triggered()));

    openProjectAction = new QAction(QIcon("img/icones/open.png"),"Ouvrir",this);
    openProjectAction->setShortcut(QKeySequence("Ctrl+O"));
    openProjectAction->setStatusTip("Ouvrir un projet");

    saveProjectAction = new QAction(QIcon("img/icones/save1.png"),"Enregistrer", this);
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
    startWindowDialog->getNewProjectButton()->setMinimumWidth(150);

    startWindowDialog->getOpenProjectButton()->setDefaultAction(openProjectAction);
    startWindowDialog->getOpenProjectButton()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    startWindowDialog->getOpenProjectButton()->setIconSize(QSize(30,30));
    startWindowDialog->getOpenProjectButton()->setMinimumWidth(150);

}

/*
  Creer la barre de menu
*/
void MainWindow::createMenuBar()
{
    Projet& projectInstance = project();

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
    fileToolBar->addAction(openProjectAction);
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

    QDockWidget * chutierDock = new QDockWidget("Chutier", this);
    chutier = new Chutier( chutierDock );
    chutierDock->setWidget(chutier);
    addDockWidget(Qt::TopDockWidgetArea, chutierDock);
    viewMenu->addAction(chutier->_viewerChutierDock->toggleViewAction());

    //Dock Timeline

    QDockWidget * timelineDock = new QDockWidget("Timeline",this);
    timeline = new TimeLineUi( timelineDock );
    timelineDock->setWidget(timeline);
    addDockWidget(Qt::BottomDockWidgetArea, timelineDock);

    //Dock UndoWidget

    QDockWidget * undoDock = new QDockWidget("Command List");
    
    undoView = new UndoView(Projet::getInstance().getCommandManager());
    undoWidget = new UndoWidget(undoView);
    undoDock->setWidget(undoWidget);
    viewMenu->addAction(undoDock->toggleViewAction());

    //Dock Viewer

    createWidgetViewer();

    //Dock essai QML

    QDockWidget * dockGraphicTimeline = new QDockWidget("Timeline Graphique");
//    _timelineGraphique = new TimelineGraphique(dockGraphicTimeline);
//    dockGraphicTimeline->setWidget(_timelineGraphique);
//    viewMenu->addAction(dockGraphicTimeline->toggleViewAction());
}


void MainWindow::createWidgetViewer()
{

    QDockWidget * contentViewerDock = new QDockWidget("Viewer",this);
    viewerImg = new ViewerTweedy( contentViewerDock );
    contentViewerDock->setWidget(viewerImg);
    addDockWidget(Qt::TopDockWidgetArea, contentViewerDock);
    
    viewMenu->addAction(contentViewerDock->toggleViewAction());
    
    viewerImg->getCaptureButton()->setDefaultAction(_captureAction);
    viewerImg->getCaptureButton()->setIconSize(QSize(50,50));

    //connexions boutons du viewer avec actions de la timeline
    viewerImg->getNextButton()->setDefaultAction(timeline->getNextAction());
    viewerImg->getNextButton()->setIconSize(QSize(25,25));
    viewerImg->getPlayPauseButton()->setDefaultAction(timeline->getPlayPauseAction());
    viewerImg->getPlayPauseButton()->setIconSize(QSize(25,25));
    viewerImg->getPreviousButton()->setDefaultAction(timeline->getPreviousAction());
    viewerImg->getPreviousButton()->setIconSize(QSize(25,25));
    viewerImg->getRetour0Button()->setDefaultAction(timeline->getRetour0Action());
    viewerImg->getRetour0Button()->setIconSize(QSize(20,20));
    //timer
    connect(timeline, SIGNAL(timeChanged(int)), this, SLOT(writeTime(int)));
    //connection slider
    viewerImg->getTempsSlider()->setTickPosition(QSlider::TicksAbove);
    //signal : valueChanged() : Emitted when the slider's value has changed.
    connect(viewerImg->getTempsSlider(),SIGNAL(valueChanged(int)), this, SLOT(writeTime(int)));
    viewerImg->getTempsSlider()->setMaximum(timeline->getTimeline()->maxTime());
}


void MainWindow::on_captureAction_triggered()
{
    Projet& projectInstance = project();

    int isConnected = projectInstance.tryToConnectCamera();
    std::cout<<"IS CONNECTED ?"<<isConnected<<std::endl;
    if (isConnected == 0)
    {
        QMessageBox::about(this, tr("Warning"), tr("No camera connected to the computer"));
        std::cout<<"No camera connected to the computer"<<std::endl;
    }
    else
    {
        std::cout<<"Camera connected"<<std::endl;
        
        //without action
        
        projectInstance.setFolderToSavePictures();

        //Give picture to application and timeline
        //boost::filesystem::path fn = projectInstance.captureToFile();
        boost::filesystem::path fn = projectInstance.gPhotoInstance().captureToFile();
        Clip clipFromPicture (fn);
        Timeline& timeline = projectInstance.getTimeline();
        clipFromPicture.setPosition(timeline.maxTime(), timeline.maxTime()+1 );
        projectInstance.addImedia( clipFromPicture );
        timeline.addClip(clipFromPicture);
        timeline.setMaxTime();
       
        
        //with action
        /*
        ActCapturePicture action;
        
        action();
         * */
    }

}

void MainWindow::on_newProjectAction_triggered()
{
    newProjectDialog = new newProjectWindow(this);
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
}


void MainWindow::on_undoButton_clicked(){
    
    CommandManager& cmdMng = (Projet::getInstance()).getCommandManager();
    if(cmdMng.canUndo()){
        cmdMng.undo();
    }
}

void MainWindow::on_redoButton_clicked(){
    
    CommandManager& cmdMng = (Projet::getInstance()).getCommandManager();
    if(cmdMng.canRedo()){
        cmdMng.redo();
    }
}

//_______________ Write time in label and select the good cell _________________

void MainWindow::writeTime(int newValue)
{

    timeline->getTableWidget()->setCurrentCell(0,newValue);

    if (newValue == timeline->getTimeline()->maxTime())
        newValue = -1;

    viewerImg->getTimeLabel()->setNum(newValue);
    viewerImg->getTempsSlider()->setSliderPosition(newValue);
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

}
