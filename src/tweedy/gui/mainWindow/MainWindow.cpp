#include "MainWindow.hpp"

#include <tweedy/core/Projet.hpp>
#include <tweedy/core/action/ActCapturePicture.hpp>
#include <tweedy/core/command/GroupeUndoRedoCmd.hpp>
#include <tweedy/core/command/clip/CmdClipSetTimeRange.hpp>

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

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

MainWindow::MainWindow()
{
	setWindowTitle( tr( "TWEEDY - stop motion software" ) );

	createActions();
	createStartWindow();
	createMenuBar();
	createToolBar();
	createWidgets();
	createStatusBar();

//	connect( this->_timelineTable, SIGNAL( timeChanged( int ) ), this->_viewerImg, SLOT( displayChanged( int ) ) );
	connect( &( this->_timelineGraphic->getTimelineDataWrapper() ), SIGNAL( timeChanged( int ) ), this->_viewerImg, SLOT( displayChanged( int ) ) );

//        this->adjustSize();

        connect( &(this->_timelineGraphic->getTimelineDataWrapper()), SIGNAL( displayChanged( int, int ) ), _chutier, SLOT( changedPixmap( int, int ) ) );

	this->adjustSize();

}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{

	_newProjectAction = new QAction( QIcon( "img/icones/new1.png" ), "New project", this );
	_newProjectAction->setShortcut( QKeySequence( "Ctrl+N" ) );
	_newProjectAction->setStatusTip( "Create a new project" );
	connect( _newProjectAction, SIGNAL( triggered() ), this, SLOT( on_newProjectAction_triggered() ) );

	_openProjectAction = new QAction( QIcon( "img/icones/open.png" ), "Open project", this );
	_openProjectAction->setShortcut( QKeySequence( "Ctrl+O" ) );
	_openProjectAction->setStatusTip( "Open a project" );
	connect( _openProjectAction, SIGNAL( triggered() ), this, SLOT( on_openProjectAction_triggered() ) );

	_saveProjectAction = new QAction( QIcon( "img/icones/save1.png" ), "Save", this );
	_saveProjectAction->setShortcut( QKeySequence( "Ctrl+S" ) );
	_saveProjectAction->setStatusTip( "Save your project" );

	_saveAsProjectAction = new QAction( "Save As", this );
	_saveProjectAction->setShortcut( QKeySequence( "Ctrl+S" ) );
	_saveProjectAction->setStatusTip( "Save your project" );
	connect( _saveAsProjectAction, SIGNAL( triggered() ), this, SLOT( on_saveAsProjectAction_triggered() ) );

	_quitAction = new QAction( QIcon( "img/icones/quit.png" ), "&Quitter", this );
	_quitAction->setShortcut( QKeySequence( "Ctrl+Q" ) );
	_quitAction->setStatusTip( "Quit Tweedy" );
	connect( _quitAction, SIGNAL( triggered() ), qApp, SLOT( quit() ) );

	_undoAction = new QAction( QIcon( "img/icones/undo.png" ), "Undo", this );
	_undoAction->setShortcut( QKeySequence( "Ctrl+Z" ) );
	connect( _undoAction, SIGNAL( triggered() ), this, SLOT( on_undoButton_clicked() ) );

	_redoAction = new QAction( QIcon( "img/icones/redo.png" ), "Redo", this );
	_redoAction->setShortcut( QKeySequence( "Shift+Ctrl+Z" ) );
	connect( _redoAction, SIGNAL( triggered() ), this, SLOT( on_redoButton_clicked() ) );

	_aboutAction = new QAction( "About Tweedy", this );
	connect( _aboutAction, SIGNAL( triggered() ), this, SLOT( on_aboutAction_triggered() ) );

	_aboutQtAction = new QAction( "About Qt", this );
	connect( _aboutQtAction, SIGNAL( triggered() ), qApp, SLOT( aboutQt() ) );

	_configAction = new QAction( "Camera configuration", this );
	connect( _configAction, SIGNAL( triggered() ), this, SLOT( on_configAction_triggered() ) );

	_captureAction = new QAction( QIcon( "img/icones/capture.png" ), "Capture", this );
	_captureAction->setShortcut( QKeySequence( "Retour" ) );
	connect( _captureAction, SIGNAL( triggered() ), this, SLOT( on_captureAction_triggered() ) );
        
        _exportAction = new QAction( "Export", this );
        _exportAction->setStatusTip( "Export your timeline" );
        connect( _exportAction, SIGNAL( triggered() ), this, SLOT( on_exportAction_triggered() ) );

	//save the project
	connect( _saveProjectAction, SIGNAL( triggered() ), this, SLOT( on_saveProjectAction_triggered() ) );

	//load the project
	connect( _openProjectAction, SIGNAL( triggered() ), this, SLOT( on_loadProjectAction_triggered() ) );

}

void MainWindow::createStartWindow()
{
	//creation of the start window
	_startWindowDialog = new StartWindow();
	/// @todo Le titre est deja sette dans StartWindow !
	/// Pourquoi ne pas tout faire dans StartWindow ??
	_startWindowDialog->setWindowTitle( tr( "TWEEDY - stop motion software" ) );
	_startWindowDialog->setWindowFlags( Qt::WindowStaysOnTopHint );
	_startWindowDialog->setModal( false );
	_startWindowDialog->showNormal();

	//pu the window on the screen center
	const QRect screen = QApplication::desktop()->screenGeometry();
	_startWindowDialog->move( screen.center() - _startWindowDialog->rect().center() );

	_startWindowDialog->getNewProjectButton()->setDefaultAction( _newProjectAction );
	_startWindowDialog->getNewProjectButton()->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
	_startWindowDialog->getNewProjectButton()->setIconSize( QSize( 40, 40 ) );
	_startWindowDialog->getNewProjectButton()->setMinimumWidth( 150 );

	_startWindowDialog->getOpenProjectButton()->setDefaultAction( _openProjectAction );
	_startWindowDialog->getOpenProjectButton()->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
	_startWindowDialog->getOpenProjectButton()->setIconSize( QSize( 40, 40 ) );
	_startWindowDialog->getOpenProjectButton()->setMinimumWidth( 150 );

	_startWindowDialog->setModal( true );
	_startWindowDialog->activateWindow();

	this->setEnabled( false );

	connect( _startWindowDialog, SIGNAL( rejected() ), this, SLOT( on_close_window() ) );
}

void MainWindow::on_close_window()
{
	this->setEnabled( true );
}

void MainWindow::createMenuBar()
{
	Projet& projectInstance = project();

	_fileMenu = menuBar()->addMenu( tr( "&File" ) );
	_fileMenu->addAction( _newProjectAction );
	_fileMenu->addAction( _openProjectAction );
	menuBar()->addSeparator();
	_fileMenu->addAction( _saveProjectAction );
	_fileMenu->addAction( _saveAsProjectAction );
        _fileMenu->addAction( _exportAction );
	_fileMenu->addAction( _quitAction );

	_editMenu = menuBar()->addMenu( tr( "&Edit" ) );
	_editMenu->addAction( _undoAction );
	_editMenu->addAction( _redoAction );

	_viewMenu = menuBar()->addMenu( tr( "View" ) );

	_paramsMenu = menuBar()->addMenu( tr( "Configuration" ) );
	_paramsMenu->addAction( _configAction );

	_helpMenu = menuBar()->addMenu( tr( "Help" ) );
	_helpMenu->addAction( _aboutAction );
	_helpMenu->addAction( _aboutQtAction );
}

void MainWindow::createToolBar()
{
	_fileToolBar = addToolBar( "File" );
	_fileToolBar->addAction( _newProjectAction );
	_fileToolBar->addAction( _openProjectAction );
	_fileToolBar->addAction( _saveProjectAction );
	_fileToolBar->addAction( _quitAction );

	_editToolBar = addToolBar( "Edit" );
	_editToolBar->addAction( _undoAction );
	_editToolBar->addAction( _redoAction );

	_fileToolBar->setIconSize( QSize( 25, 25 ) );
}

void MainWindow::createWidgets()
{
	{
		// Dock Chutier
		QDockWidget * chutierDock = new QDockWidget( "Media List", this );
		{
			_chutier = new Chutier( chutierDock );
			chutierDock->setWidget( _chutier );
			addDockWidget( Qt::TopDockWidgetArea, chutierDock );
			_viewMenu->addAction( chutierDock->toggleViewAction() );
			_viewMenu->addAction( _chutier->_viewerChutierDock->toggleViewAction() );
		}
		// Dock UndoWidget
		QDockWidget * undoDock = new QDockWidget( "Command List", this );
		{
			_undoView = new UndoView( Projet::getInstance().getCommandManager(), undoDock );
			_undoWidget = new UndoWidget( _undoView );
			undoDock->setWidget( _undoWidget );
			addDockWidget( Qt::TopDockWidgetArea, undoDock );
			_viewMenu->addAction( undoDock->toggleViewAction() );
		}

		tabifyDockWidget( chutierDock, undoDock );
		undoDock->setHidden( true );
		undoDock->setFloating( true );
	}

//                {
//                        // Dock Timeline Table
//                        QDockWidget * timelineDock = new QDockWidget( "Timeline", this );
//                        _timelineTable = new TimelineTable( timelineDock );
//                        timelineDock->setWidget( _timelineTable );
//                        addDockWidget( Qt::BottomDockWidgetArea, timelineDock );
//                        _viewMenu->addAction( timelineDock->toggleViewAction() );

//                        connect( _timelineTable->getTableWidget(), SIGNAL( cellDoubleClicked( int, int ) ), _chutier, SLOT( changedPixmap( int, int ) ) );
//                        connect( _timelineTable, SIGNAL( timeChanged( int ) ), this, SLOT( writeTime( int ) ) );
//                }

	{
		// Dock Timeline QML
		QDockWidget * graphicTimelineDock = new QDockWidget( "Graphic Timeline", this );
		_timelineGraphic = new TimelineGraphic( NULL );
		graphicTimelineDock->setWidget( _timelineGraphic );
		addDockWidget( Qt::BottomDockWidgetArea, graphicTimelineDock );

		_viewMenu->addAction( graphicTimelineDock->toggleViewAction() );

	}

	// Dock Viewer
	createWidgetViewer();
}

void MainWindow::createWidgetViewer()
{
	QDockWidget * contentViewerDock = new QDockWidget( "Viewer", this );
	_viewerImg = new ViewerTweedy( contentViewerDock );
	contentViewerDock->setWidget( _viewerImg );
	addDockWidget( Qt::TopDockWidgetArea, contentViewerDock );

	_viewMenu->addAction( contentViewerDock->toggleViewAction() );

	_viewerImg->getCaptureButton()->setDefaultAction( _captureAction );
	_viewerImg->getCaptureButton()->setIconSize( QSize( 60, 60 ) );

	/// @todo ne pas appeler la timeline depuis le viewer !
	/// Mais emettre des signaux dans chacun et repasser par la MainWindow,
	/// pour changer le temps.
	//connexions boutons du viewer avec actions de la timeline
	//        _viewerImg->getNextButton()->setDefaultAction( _timelineTable->getNextAction() );
	//        _viewerImg->getNextButton()->setIconSize( QSize( 30, 30 ) );
	//        _viewerImg->getPlayPauseButton()->setDefaultAction( _timelineTable->getPlayPauseAction() );
	//        _viewerImg->getPlayPauseButton()->setIconSize( QSize( 30, 30 ) );
	//        _viewerImg->getPreviousButton()->setDefaultAction( _timelineTable->getPreviousAction() );
	//        _viewerImg->getPreviousButton()->setIconSize( QSize( 30, 30 ) );
	//        _viewerImg->getRetour0Button()->setDefaultAction( _timelineTable->getRetour0Action() );
	//        _viewerImg->getRetour0Button()->setIconSize( QSize( 30, 30 ) );
	//timer
	//connection slider
	_viewerImg->getTempsSlider()->setTickPosition( QSlider::TicksAbove );
	//signal : valueChanged() : Emitted when the slider's value has changed.
	connect( _viewerImg->getTempsSlider(), SIGNAL( valueChanged( int ) ), this, SLOT( writeTime( int ) ) );
	//        _viewerImg->getTempsSlider()->setMaximum( _timelineTable->getTimeline().getMaxTime() );

}

void MainWindow::on_captureAction_triggered()
{
	Projet& projectInstance = project();

	int isConnected = projectInstance.tryToConnectCamera();
	if( isConnected == 0 )
	{
		QMessageBox::about( this, tr( "Warning" ), tr( "No camera connected to the computer" ) );
	}
	else
	{
		//take HD picture
		Projet& project = Projet::getInstance();

		project.gPhotoInstance().setFolderToSavePictures( project.getProjectFolder() );

		//take the picture's filename
		boost::filesystem::path filenameHD = project.gPhotoInstance().captureToFile();

		//make a LD picture
		QImage img( QString::fromStdString( filenameHD.string() ) );
		QImage petiteImg = img.scaled( QSize( 600, 350 ) );

                std::string filenameLD = filenameHD.string();
                filenameLD.insert( filenameLD.size() - 4, "_LD" );
                int pos = filenameLD.find("HD/");
                filenameLD.erase(filenameLD.begin()+37, filenameLD.begin()+40);

		petiteImg.save( QString::fromStdString( filenameLD ) );

		ActCapturePicture action;
		action( filenameLD );

		//update chutier
		ListWidget & listWidgetCapture = _chutier->getListWidgetCapture();
		QListWidgetItem *item = new QListWidgetItem( QIcon( QString::fromStdString( filenameLD ) ), QString::fromStdString( filenameLD ), &listWidgetCapture );

		listWidgetCapture.addItem( item );

		_chutier->getTabWidget().setCurrentWidget( &listWidgetCapture );
		/*add to chutier core*/

	}

}

void MainWindow::on_newProjectAction_triggered()
{
	_newProjectDialog = new newProjectWindow( this );
	_newProjectDialog->show();
	_startWindowDialog->hide();

	connect( _newProjectDialog, SIGNAL( rejected() ), this, SLOT( on_close_window() ) );
	connect( _newProjectDialog, SIGNAL( accepted() ), this, SLOT( on_acceptedNewProjectWindow() ) );

	connect( _newProjectDialog->getSearchFolderProjectButton(), SIGNAL( clicked() ), this, SLOT( on_searchFolderProjectButton_clicked() ) );
}

void MainWindow::on_searchFolderProjectButton_clicked()
{
	QFileDialog * fileDialog = new QFileDialog();
	QString fileName = fileDialog->getExistingDirectory( this, tr( "Choose folder for project" ), QString( boost::filesystem::initial_path().string().c_str() ) );

	_newProjectDialog->getFolderProjectLineEdit()->setText( fileName );

	//set the name folder for the project files
	Projet& projectInstance = Projet::getInstance();
	boost::filesystem::path pathFolder( fileName.toStdString() );
	projectInstance.setProjectFolder( pathFolder );

	/*Create corresponding folders*/
	pathFolder /= "projet";
        boost::filesystem::create_directory( pathFolder );
	boost::filesystem::path pathFolderPictures = pathFolder / "pictures";
	boost::filesystem::create_directory( pathFolderPictures );
        boost::filesystem::path pathFolderPicturesHD = pathFolderPictures / "HD";
        boost::filesystem::create_directory( pathFolderPicturesHD );
}

//fonction a completer pour creer un nouveau projet

void MainWindow::on_acceptedNewProjectWindow()
{

	this->setEnabled( true );

}

void MainWindow::on_openProjectAction_triggered()
{
	_startWindowDialog->hide();
	QFileDialog * fileDialog = new QFileDialog();
	fileDialog->setAcceptMode( QFileDialog::AcceptOpen );

	QString fileName = fileDialog->getOpenFileName( this, tr( "Open a project" ), QString( boost::filesystem::initial_path().string().c_str() ), "*.txt" );

	this->setEnabled( true );

	//plus qu a recuperer le fileName pour ouvrir le projet sauvegarde
}

void MainWindow::on_saveAsProjectAction_triggered()
{
	QFileDialog * fileDialog = new QFileDialog();
	fileDialog->setAcceptMode( QFileDialog::AcceptSave );
	QString fileName = fileDialog->getSaveFileName( this, tr( "Save as a project" ), QString( boost::filesystem::initial_path().string().c_str() ), "*.txt" );
}

void MainWindow::on_undoButton_clicked()
{

	CommandManager& cmdMng = ( Projet::getInstance() ).getCommandManager();
	if( cmdMng.canUndo() )
	{
		cmdMng.undo();
	}

}

void MainWindow::on_redoButton_clicked()
{

	CommandManager& cmdMng = ( Projet::getInstance() ).getCommandManager();
	if( cmdMng.canRedo() )
	{
		cmdMng.redo();
	}

}

void MainWindow::on_aboutAction_triggered()
{

	_aboutWindow = new AboutTweedy( this );
	_aboutWindow->exec();

}

void MainWindow::on_configAction_triggered()
{
	QDockWidget * configCameraDock = new QDockWidget( "Camera Configuration", this );
	{
		_configCamera = new ConfigCamera( configCameraDock );
		configCameraDock->setWidget( ( _configCamera ) );
		addDockWidget( Qt::TopDockWidgetArea, configCameraDock );

	}
	configCameraDock->setFloating( true );
}

//_______________ Write time in label and select the good cell _________________

void MainWindow::writeTime( int newValue )
{
//	_timelineTable->getTableWidget()->setCurrentCell( 0, newValue );

//	if( newValue == _timelineTable->getTimeline().getMaxTime() )
//		newValue = -1;

	_viewerImg->getTimeLabel()->setNum( newValue );
	_viewerImg->getTempsSlider()->setSliderPosition( newValue );

	_timelineGraphic->getTimelineDataWrapper()._currentTime = newValue;
}

/*
  Create the status bar
 */
void MainWindow::createStatusBar()
{

	_statusBar = statusBar();
	_statusBar->showMessage( "Ready" );

}

//save the project

void MainWindow::on_saveProjectAction_triggered()
{
	//make an archive
	const char * filename = "./saveProjectTweedy.txt";
	std::ofstream ofs( filename );
	boost::archive::text_oarchive oa( ofs );
	oa << project();
        ofs.close();
}


//load the project

void MainWindow::on_loadProjectAction_triggered()
{
	// open the archive
	const char * filename = "./saveProjectTweedy.txt";
	std::ifstream ifs( filename );
	boost::archive::text_iarchive ia( ifs );

	ia >> project();
        
        //_timelineTable->updateTable();
        _chutier->updateChutier();

}



void MainWindow::on_exportAction_triggered()
{
    _exportWidget = new ExportWidget( );
    _exportWidget->show();

}





std::string MainWindow::generateTimeData(int value, int choosenFps, int absoluteFps)
{
    double cAbsoluteFps = static_cast<double>(absoluteFps);
    
    //convertir la lgr du clip en base 24
    int nbframe = value * (absoluteFps/choosenFps);
    int hour = nbframe/std::pow(cAbsoluteFps,3);
    int min = (nbframe % static_cast<int>(std::pow(cAbsoluteFps,3)))/std::pow(cAbsoluteFps,2);
    int sec = (nbframe % static_cast<int>(std::pow(cAbsoluteFps,2)))/absoluteFps;
    nbframe = nbframe % absoluteFps ;
    
    std::string shour = hour<10 ? "0"+boost::lexical_cast<std::string>(hour) 
            : boost::lexical_cast<std::string>(hour);

    std::string smin = min<10 ? "0"+boost::lexical_cast<std::string>(min) 
            : boost::lexical_cast<std::string>(min);

    std::string ssec = sec<10 ? "0"+boost::lexical_cast<std::string>(sec) 
            : boost::lexical_cast<std::string>(sec);

    std::string sframe = nbframe<10 ? "0"+boost::lexical_cast<std::string>(nbframe) 
            : boost::lexical_cast<std::string>(nbframe);

    return shour + ":" + smin + ":" + ssec + ":" + sframe ;
}
