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
#include <QtGui/QApplication>
#include <QtGui/QImage>

#include <tweedy/core/command/GroupeUndoRedoCmd.hpp>
#include <tweedy/core/command/clip/CmdClipSetTimeRange.hpp>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

#include <tweedy/core/action/ActCapturePicture.hpp>

#include <iostream>

#include <iomanip>

#include <fstream>
#include <string>


MainWindow::MainWindow()
{
    setWindowTitle(tr("TWEEDY - stop motion software"));

    createActions();
    createStartWindow();
    createMenuBar();
    createToolBar();
    createWidgets();
    createStatusBar();

    Projet& projectInstance = project();

    connect(this->timeline, SIGNAL( timeChanged(int) ), this->viewerImg, SLOT(displayChanged(int)) );


    this->adjustSize();
}



/*
  Creer toutes les actions de l'projet
*/
void MainWindow::createActions()
{

    newProjectAction = new QAction(QIcon("img/icones/new1.png"),"New project", this);
    newProjectAction->setShortcut(QKeySequence("Ctrl+N"));
    newProjectAction->setStatusTip("Create a new project");
    connect(newProjectAction, SIGNAL(triggered()), this, SLOT(on_newProjectAction_triggered()));

    openProjectAction = new QAction(QIcon("img/icones/open.png"),"Open project",this);
    openProjectAction->setShortcut(QKeySequence("Ctrl+O"));
    openProjectAction->setStatusTip("Open a project");
    connect(openProjectAction, SIGNAL(triggered()), this, SLOT(on_openProjectAction_triggered()));

    saveProjectAction = new QAction(QIcon("img/icones/save1.png"),"Save", this);
    saveProjectAction->setShortcut(QKeySequence("Ctrl+S"));
    saveProjectAction->setStatusTip("Save your project");

    saveAsProjectAction = new QAction("Save As", this);
    saveProjectAction->setShortcut(QKeySequence("Ctrl+S"));
    saveProjectAction->setStatusTip("Save your project");
    connect(saveAsProjectAction,SIGNAL(triggered()), this, SLOT(on_saveAsProjectAction_triggered()));

    quitAction = new QAction(QIcon("img/icones/quit.png"),"&Quitter", this);
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    quitAction->setStatusTip("Quit Tweedy");
    connect(quitAction, SIGNAL(triggered()), qApp,SLOT(quit()));

    undoAction = new QAction(QIcon("img/icones/undo.png"),"Undo",this);
    undoAction->setShortcut(QKeySequence("Ctrl+Z"));

    redoAction = new QAction(QIcon("img/icones/redo.png"),"Redo",this);
    redoAction->setShortcut(QKeySequence("Shift+Ctrl+Z"));

    aboutAction = new QAction("About Tweedy",this);

    aboutQtAction = new QAction("About Qt",this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    
    connect(undoAction, SIGNAL(triggered()), this, SLOT(on_undoButton_clicked()));
    connect(redoAction, SIGNAL(triggered()), this, SLOT(on_redoButton_clicked()));

    _captureAction = new QAction(QIcon("img/icones/capture.png"),"Capture",this);
    _captureAction->setShortcut(QKeySequence("Retour"));
    connect(_captureAction, SIGNAL(triggered()), this,SLOT(on_captureAction_triggered()));
    
    //save the project
    connect(saveProjectAction, SIGNAL(triggered()), this,SLOT(on_saveProjectAction_triggered()));

    //load the project
    connect(openProjectAction, SIGNAL(triggered()), this,SLOT(on_loadProjectAction_triggered()));

}



void MainWindow::createStartWindow()
{

    //creation fenetre de demarrage
    startWindowDialog = new StartWindow();
    startWindowDialog->setWindowTitle(tr("TWEEDY - stop motion software"));
    startWindowDialog->setWindowFlags(Qt::WindowStaysOnTopHint);
    startWindowDialog->setModal(false);
    startWindowDialog->showNormal();

    //mettre la fenetre au centre de l'ecran
    const QRect screen = QApplication::desktop()->screenGeometry();
    startWindowDialog->move(screen.center() - startWindowDialog->rect().center());

    startWindowDialog->getNewProjectButton()->setDefaultAction(newProjectAction);
    startWindowDialog->getNewProjectButton()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    startWindowDialog->getNewProjectButton()->setIconSize(QSize(40,40));
    startWindowDialog->getNewProjectButton()->setMinimumWidth(150);

    startWindowDialog->getOpenProjectButton()->setDefaultAction(openProjectAction);
    startWindowDialog->getOpenProjectButton()->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    startWindowDialog->getOpenProjectButton()->setIconSize(QSize(40,40));
    startWindowDialog->getOpenProjectButton()->setMinimumWidth(150);

    startWindowDialog->setModal(true);
    startWindowDialog->activateWindow();

    this->setEnabled(false);

    connect( startWindowDialog, SIGNAL(rejected()), this, SLOT(on_close_window()) );
}

void MainWindow::on_close_window()
{
    this->setEnabled(true);
}

/*
  Creer la barre de menu
*/
void MainWindow::createMenuBar()
{
    Projet& projectInstance = project();

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newProjectAction);
    fileMenu->addAction(openProjectAction);
    menuBar()->addSeparator();
    fileMenu->addAction(saveProjectAction);
    fileMenu->addAction(saveAsProjectAction);
    fileMenu->addAction(quitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    viewMenu = menuBar()->addMenu(tr("View"));

    paramsMenu = menuBar()->addMenu(tr("Configuration"));

    helpMenu = menuBar()->addMenu(tr("Help"));
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

    fileToolBar->setIconSize(QSize(25,25));
}


/*
  Creer tous les widgets
*/
void MainWindow::createWidgets()
{
    //Dock Chutier

    QDockWidget * chutierDock = new QDockWidget("Media List", this);
    chutier = new Chutier( chutierDock );
    chutierDock->setWidget(chutier);
    addDockWidget(Qt::TopDockWidgetArea, chutierDock);
    viewMenu->addAction(chutierDock->toggleViewAction());
    viewMenu->addAction(chutier->_viewerChutierDock->toggleViewAction());

    //Dock Timeline

    QDockWidget * timelineDock = new QDockWidget("Timeline",this);
    timeline = new TimeLineUi( timelineDock );
    timelineDock->setWidget(timeline);
    addDockWidget(Qt::BottomDockWidgetArea, timelineDock);
    viewMenu->addAction(timelineDock->toggleViewAction());

    //Dock Viewer

    createWidgetViewer();

    //Dock UndoWidget

    QDockWidget * undoDock = new QDockWidget("Command List");

    undoView = new UndoView(Projet::getInstance().getCommandManager());
    undoWidget = new UndoWidget(undoView);
    undoDock->setWidget(undoWidget);
    viewMenu->addAction(undoDock->toggleViewAction());

    //Dock essai QML

    QDockWidget * dockGraphicTimeline = new QDockWidget("Graphic Timeline");
    _timelineGraphique = new TimelineGraphique(dockGraphicTimeline);
    dockGraphicTimeline->setWidget(_timelineGraphique);
    viewMenu->addAction(dockGraphicTimeline->toggleViewAction());


    //Dock Config Camera

    QDockWidget * configCameraDock = new QDockWidget("Camera Configuration");
    _configCamera =  new ConfigCamera(configCameraDock);
    configCameraDock->setWidget((_configCamera));
    viewMenu->addAction(configCameraDock->toggleViewAction());
}


void MainWindow::createWidgetViewer()
{

    QDockWidget * contentViewerDock = new QDockWidget("Viewer",this);
    viewerImg = new ViewerTweedy( contentViewerDock );
    contentViewerDock->setWidget(viewerImg);
    addDockWidget(Qt::TopDockWidgetArea, contentViewerDock);
    
    viewMenu->addAction(contentViewerDock->toggleViewAction());
    
    viewerImg->getCaptureButton()->setDefaultAction(_captureAction);
    viewerImg->getCaptureButton()->setIconSize(QSize(60,60));

    //connexions boutons du viewer avec actions de la timeline
    viewerImg->getNextButton()->setDefaultAction(timeline->getNextAction());
    viewerImg->getNextButton()->setIconSize(QSize(30,30));
    viewerImg->getPlayPauseButton()->setDefaultAction(timeline->getPlayPauseAction());
    viewerImg->getPlayPauseButton()->setIconSize(QSize(30,30));
    viewerImg->getPreviousButton()->setDefaultAction(timeline->getPreviousAction());
    viewerImg->getPreviousButton()->setIconSize(QSize(30,30));
    viewerImg->getRetour0Button()->setDefaultAction(timeline->getRetour0Action());
    viewerImg->getRetour0Button()->setIconSize(QSize(30,30));
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
    //std::cout<<"IS CONNECTED ?"<<isConnected<<std::endl;
    if (isConnected == 0)
    {
        QMessageBox::about(this, tr("Warning"), tr("No camera connected to the computer"));
        //std::cout<<"No camera connected to the computer"<<std::endl;
    }
    else
    {
        //std::cout<<"Camera connected"<<std::endl;
        
        //without action




        //Give picture to application and timeline
        /*projectInstance.gPhotoInstance().setFolderToSavePictures(projectInstance.getProjectFolder());
        boost::filesystem::path fn = projectInstance.gPhotoInstance().captureToFile();
        std::cout<<"FN : "<<fn<<std::endl;

        Timeline& timeline = projectInstance.getTimeline();
        Clip clipFromPicture (fn,timeline.getId(),"clip" + boost::lexical_cast<std::string>(timeline.getNbClip()++));
        clipFromPicture.setPosition(timeline.maxTime(), timeline.maxTime()+1 );
        projectInstance.addImedia( clipFromPicture );
        timeline.addClip(clipFromPicture);*/


        
        //with action
        
        //prendre la photo HD
        
        Projet& project = Projet::getInstance();

        project.gPhotoInstance().setFolderToSavePictures(project.getProjectFolder());
    
        //recuperer le filename de la picture
        boost::filesystem::path filenameHD = project.gPhotoInstance().captureToFile();
        
        //faire une image LD
        QImage img(QString::fromStdString(filenameHD.string()));
        QImage petiteImg = img.scaled(QSize(600,350));
        
        std::string filenameLD = filenameHD.string();
        filenameLD.insert(filenameLD.size()-4, "_LD");
        petiteImg.save(QString::fromStdString(filenameLD));
        
        

        ActCapturePicture action;
        action(filenameLD);

    }

}

void MainWindow::on_newProjectAction_triggered()
{
    newProjectDialog = new newProjectWindow(this);
    newProjectDialog->show();
    startWindowDialog->hide();

    connect( newProjectDialog, SIGNAL(rejected()), this, SLOT(on_close_window()) );
    connect( newProjectDialog, SIGNAL(accepted()), this, SLOT(on_acceptedNewProjectWindow()));

    connect(newProjectDialog->getSearchFolderProjectButton(),SIGNAL(clicked()), this, SLOT(on_searchFolderProjectButton_clicked()));
}

void MainWindow::on_searchFolderProjectButton_clicked()
{
    QFileDialog * fileDialog = new QFileDialog();
    QString fileName =fileDialog->getExistingDirectory(this,
                                                    tr("Choose folder for project"),
                                                    QString(boost::filesystem::initial_path().string().c_str()));

    newProjectDialog->getFolderProjectLineEdit()->setText(fileName);

    //set the name folder for the project files
    Projet& projectInstance = Projet::getInstance();
    boost::filesystem::path pathFolder(fileName.toStdString());
    projectInstance.setProjectFolder(pathFolder);
    std::cout<<pathFolder<<std::endl;
    /*Create corresponding folders*/
    pathFolder/="projet";
    std::cout<<pathFolder<<std::endl;
    boost::filesystem::create_directory(pathFolder);
    boost::filesystem::path pathFolderPictures = pathFolder/"pictures";
    boost::filesystem::create_directory(pathFolderPictures);
    //projectInstance.gPhotoInstance().setFolderToSavePictures(pathFolder/*Pictures*/);
}

//fonction a completer pour creer un nouveau projet
void MainWindow::on_acceptedNewProjectWindow(){

    this->setEnabled(true);

}

void MainWindow::on_openProjectAction_triggered()
{
    startWindowDialog->hide();
    QFileDialog * fileDialog = new QFileDialog();
    fileDialog->setAcceptMode(QFileDialog::AcceptOpen);

    QString fileName =fileDialog->getOpenFileName(this,tr("Open a project"),QString(boost::filesystem::initial_path().string().c_str()),"*.txt");

    this->setEnabled(true);

    //plus qu a recuperer le fileName pour ouvrir le projet sauvegarde
}

void MainWindow::on_saveAsProjectAction_triggered()
{
    QFileDialog * fileDialog = new QFileDialog();
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    QString fileName =fileDialog->getSaveFileName(this, tr("Save as a project"),QString(boost::filesystem::initial_path().string().c_str()),"*.txt");
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
    myStatusBar->showMessage("Ready");

}


//sauvegarde du projet
void MainWindow::on_saveProjectAction_triggered()
{
    //make an archive
    const char * filename = "./saveProjectTweedy.txt";
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << project();
    
    //std::cout << "sauvegarde" << std::endl;
}

/*
void save_schedule(const bus_schedule &s, const char * filename){
    // make an archive
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << s;
}
*/

//chargement du projet
void MainWindow::on_loadProjectAction_triggered()
{
    // open the archive
    const char * filename = "./saveProjectTweedy.txt";
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia(ifs);

    ia >> project();

    //std::cout << "chargement" << std::endl;
    timeline->updateTable();

}

MainWindow::~MainWindow()
{

}
