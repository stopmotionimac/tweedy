#include "Chutier.hpp"

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


Chutier::Chutier( QWidget *parent )
: QWidget( parent )
{
	//create widgets
	_tabWidget = new QTabWidget( this );
	_listWidgetCapture = new ListWidget( this );
	_listWidgetImport = new ListWidget( this );
	_importButton = new QToolButton( this );
	_deleteButton = new QToolButton( this );

	_tabWidget->addTab( _listWidgetImport, QIcon( "img/icones/import.png" ), "Imported" );
	_tabWidget->addTab( _listWidgetCapture, QIcon( "img/icones/capture.png" ), "Captured" );

	//create actions
	_importAction = new QAction( QIcon( "img/icones/import.png" ), "Import", this );
	_deleteAction = new QAction( QIcon( "img/icones/delete.png" ), "Delete", this );

        //actions to QToolButton
	_importButton->setDefaultAction( _importAction );
	_deleteButton->setDefaultAction( _deleteAction );
	_importButton->setIconSize( QSize( 25, 25 ) );
	_importButton->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
	_deleteButton->setIconSize( QSize( 25, 25 ) );
	_deleteButton->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );

	//create dockable widget
	_viewerChutierDock = new QDockWidget( "Media List Viewer", this );
	_viewerChutier = new QLabel( _viewerChutierDock );
	_viewerChutier->setBackgroundRole( QPalette::Dark );
        _viewerChutierDock->setWidget( _viewerChutier );


        _viewerChutier->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        _viewerChutier->setScaledContents( false );

        //widgets disposition
	QHBoxLayout * layoutBoutons = new QHBoxLayout();
        layoutBoutons->addStretch();
	layoutBoutons->addWidget( _importButton );
	layoutBoutons->addWidget( _deleteButton );

	QVBoxLayout * layoutChutier = new QVBoxLayout();
	layoutChutier->addWidget( _tabWidget );
	layoutChutier->addLayout( layoutBoutons );

	//QSplitter* splitter = new QSplitter(this);
	QHBoxLayout *mainLayout = new QHBoxLayout( this );
	mainLayout->addLayout( layoutChutier );
	//mainLayout->addWidget(splitter);
	mainLayout->addWidget( _viewerChutierDock );
	setLayout( mainLayout );


	Projet& projectInstance = Projet::getInstance();

        //to add media to chutier media ext
	ChutierMediaExt chutierMediaExt = projectInstance.getChutierMediaExt();

	boost::ptr_unordered_map<std::string, MediaExt>::iterator iter;

	for( iter = chutierMediaExt.getMapMediaExt().begin(); iter != chutierMediaExt.getMapMediaExt().end(); ++iter )
	{
		std::cout << iter->first << std::endl;
		/*path*/
		QString image( iter->first.data() );
		/*item*/
		QListWidgetItem *item = new QListWidgetItem( QIcon( image ), image, _listWidgetImport );
		/*add item to list*/
		_listWidgetImport->addItem( item );
	}

	/*to add media to chutier pictures*/
	ChutierMediaExt chutierPicture = projectInstance.getChutierPictures();

	boost::ptr_unordered_map<std::string, MediaExt>::iterator iterP;

	for( iterP = chutierPicture.getMapMediaExt().begin(); iterP != chutierPicture.getMapMediaExt().end(); ++iterP )
	{
		std::cout << iterP->first << std::endl;
		/*path*/
		QString image( iterP->first.data() );
		/*item*/
		QListWidgetItem *item = new QListWidgetItem( QIcon( image ), image, _listWidgetCapture );
		/*add item to list*/
		_listWidgetCapture->addItem( item );
	}

        QPixmap defaultImage( "img/noPhotoSelected.jpg" );
        _viewerChutier->setMinimumSize(defaultImage.width(),defaultImage.height());
        QPixmap p1( defaultImage.scaled ( _viewerChutier->width(), _viewerChutier->height(), Qt::KeepAspectRatioByExpanding ) );
        _viewerChutier->setPixmap( p1 );
        _viewerChutier->adjustSize();

	connect( _listWidgetImport, SIGNAL( itemSelectionChanged() ), this, SLOT( on_photo_selected_import() ) );
	connect( _listWidgetCapture, SIGNAL( itemSelectionChanged() ), this, SLOT( on_photo_selected_capture() ) );
	connect( _importAction, SIGNAL( triggered() ), this, SLOT( on_importAction_triggered() ) );
        connect( _deleteAction, SIGNAL( triggered() ), this, SLOT( on_deleteAction_triggered() ) );
}

void Chutier::on_photo_selected_import()
{
	QPixmap pixmap( _listWidgetImport->currentItem()->text() );
        pixmap.scaled( _viewerChutier->size(), Qt::KeepAspectRatioByExpanding );
	_viewerChutier->setPixmap( pixmap );

}

void Chutier::on_photo_selected_capture()
{
	QPixmap pixmap( _listWidgetCapture->currentItem()->text() );
	pixmap.scaled( _viewerChutier->width(), _viewerChutier->height(), Qt::KeepAspectRatioByExpanding );
	_viewerChutier->setPixmap( pixmap );

}

void Chutier::on_importAction_triggered()
{
	QStringList fileNames = QFileDialog::getOpenFileNames( this, tr( "Open Picture" ), QDir::currentPath() );

	Projet& projectInstance = Projet::getInstance();

	BOOST_FOREACH( const QString& fileName, fileNames )
	{
		QListWidgetItem *item = new QListWidgetItem( QIcon( fileName ), fileName, _listWidgetImport );

		_listWidgetImport->addItem( item );

		_tabWidget->setCurrentWidget( _listWidgetImport );

		/*add media imported to chutier core*/
		boost::filesystem::path nameOfFileToImport( fileName.toStdString() );
		ChutierMediaExt chutierMediaExt = projectInstance.getChutierMediaExt();
		chutierMediaExt.importMediaToChutier( nameOfFileToImport );
                chutierMediaExt.printMapMediaExt();
  //OK          //std::cout<<&chutierMediaExt<<std::endl
  //COHERANT    //std::cout<<chutierMediaExt.getMapMediaExt().size()<<std::endl;
	}
}

void Chutier::on_deleteAction_triggered()
{
	//bug quand on supprime tout
	QList<QListWidgetItem *> fileSelected = _listWidgetImport->selectedItems();
	for( int i = 0; i < fileSelected.count(); ++i )
	{
		if( _listWidgetImport->count() != 0 )
		{
			QListWidgetItem * item = _listWidgetImport->takeItem( i );
			delete item;
		}

	}
}

void Chutier::changedPixmap( int row, int column )
{
	Timeline* timeline = &( Projet::getInstance().getTimeline() );
	std::string idClip = "";
	std::string filename = "img/none.jpg";
	bool isClip = timeline->findCurrentClip( idClip, column );
	if( isClip )
	{
		filename = timeline->mapClip()[idClip].imgPath().string();
	}
	QPixmap img( QString::fromStdString( filename ) );
	_viewerChutier->setPixmap( img );
}

void Chutier::contextMenuEvent( QContextMenuEvent *event )
{

	QMenu menu( this );
	menu.addAction( _importAction );
	menu.exec( event->globalPos() );

}

Chutier::~Chutier()
{

}
