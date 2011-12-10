#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>


#include "MainWindow.hpp"


MainWindow::MainWindow()
{
	textEdit = new QTextEdit;
     	setCentralWidget(textEdit);

	createActions();
	
	createMenus();
	createToolBars();	

	/*QHBoxLayout *layoutH1= new QHBoxLayout;
	

	QHBoxLayout *layoutH2 = new QHBoxLayout;

	videoWidget = new QTabWidget;
     	tabWidget->addTab(new GeneralTab(fileInfo), tr("General"));
     	tabWidget->addTab(new PermissionsTab(fileInfo), tr("Permissions"));
     	tabWidget->addTab(new ApplicationsTab(fileInfo), tr("Applications"));*/



	//docks
	QDockWidget *dock1 = new QDockWidget("Dock1", this);
	addDockWidget(Qt::LeftDockWidgetArea, dock1);


	QWidget *contenuDock1 = new QWidget;
	dock1->setWidget(contenuDock1);

	_button1 = new QPushButton("Bouton 1");
	connect(_button1, SIGNAL(clicked()), this, SLOT(colorChanged()));

	_button2 = new QPushButton("Bouton 2");
	QPushButton *bouton3 = new QPushButton("Bouton 3");
	bouton3->setStyleSheet("background-color: green;");

	QLabel *labelCouleur = new QLabel("Couleur :");
	//QSpinBox *epaisseur = new QSpinBox;

	QVBoxLayout *dockLayout = new QVBoxLayout;
	dockLayout->addWidget(_button1);
	dockLayout->addWidget(_button2);
	dockLayout->addWidget(bouton3);
	dockLayout->addWidget(labelCouleur);
	//dockLayout->addWidget(epaisseur);

	contenuDock1->setLayout(dockLayout);

	QDockWidget *dock2 = new QDockWidget("Timeline", this);
	addDockWidget(Qt::BottomDockWidgetArea, dock2);

	createWindow();

	createStatusBar();

	setWindowTitle(tr("TWEEDY - logiciel de stop motion"));

	resize(800,800);


}

void MainWindow::colorChanged(){

	_button1->setStyleSheet("background-color: black;");

}

void MainWindow::open(){

	QString fileName = QFileDialog::getOpenFileName(this);
    	if (!fileName.isEmpty())
         	loadFile(fileName);

}

void MainWindow::about(){

	QMessageBox::about(this, tr("A propos de Tweedy"),
             tr("<b>Tweedy</b> est un extraordinaire logiciel de stop motion"
                " cree par de merveilleux etudiants IMAC"));


}

void MainWindow::loadFile(const QString &fileName){
}


void MainWindow::createWindow(){

	//_centralWidget = new QWidget;
	//setCentralWidget(_centralWidget);

}


void MainWindow::createActions(){

	_newAction = new QAction(QIcon("nouveau.png"), "Nouveau Projet", this);
	_newAction->setShortcut(QKeySequence("Ctrl+N"));
	_newAction->setStatusTip("Creer un nouveau projet");
	
	_openAction = new QAction("Ouvrir",this);
	_openAction->setShortcut(QKeySequence("Ctrl+O"));
	_openAction->setStatusTip("Ouvrir un projet");
	connect(_openAction, SIGNAL(triggered()), this,SLOT(open()));	


	_saveAction = new QAction(QIcon("enregistrer.png"),"&Enregistrer", this);
	_saveAction->setShortcut(QKeySequence("Ctrl+S"));
	_saveAction->setStatusTip("Enregistrer votre projet");
	
	
	_quitAction = new QAction(QIcon("quitter.png"),"&Quitter", this);
	_quitAction->setShortcut(QKeySequence("Ctrl+Q"));
	_quitAction->setStatusTip("Quitter Tweedy");
	connect(_quitAction, SIGNAL(triggered()), this,SLOT(quit()));
	
	_undoAction = new QAction(QIcon("undo.png"),"Undo",this);
	_undoAction->setShortcut(QKeySequence("Ctrl+Z"));

	_doAction = new QAction("Redo",this);
	_doAction->setShortcut(QKeySequence("Shift+Ctrl+Z"));

	_aboutAction = new QAction("A propos de Tweedy",this);
	connect(_aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	_aboutQtAction = new QAction("A propos de Qt",this);
	connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));

}


void MainWindow::createMenus(){
	
	_fileMenu = menuBar()->addMenu("&Fichier");
	_fileMenu->addAction(_newAction);
	_fileMenu->addAction(_openAction);
	menuBar()->addSeparator();
	_fileMenu->addAction(_saveAction);
	_fileMenu->addAction(_quitAction);


   	_editMenu = menuBar()->addMenu("&Edition");
	_editMenu->addAction(_undoAction);
	_editMenu->addAction(_doAction);

    	_viewMenu = menuBar()->addMenu("&Affichage");

	_TimelineMenu = menuBar()->addMenu("Timeline");

	_helpMenu = menuBar()->addMenu("Aide");
	_helpMenu->addAction(_aboutAction);
	_helpMenu->addAction(_aboutQtAction);

}

void MainWindow::createToolBars(){

	_fileToolBar = addToolBar("Fichier");
	_fileToolBar->addAction(_saveAction);
	_fileToolBar->addAction(_quitAction);

	_editToolBar = addToolBar("Edition");
	_editToolBar->addAction(_undoAction);

}

void MainWindow::createStatusBar(){

	_statusBar=statusBar();
	_statusBar->showMessage("Pret");

}
