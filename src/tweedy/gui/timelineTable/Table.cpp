#include "Table.hpp"

#include <tweedy/core/Projet.hpp>
#include <tweedy/core/action/ActDragNDropTLToTL.hpp>
#include <tweedy/core/action/ActDragNDropChutToTL.hpp>

#include <QtGui/QScrollBar>
#include <QtGui/QListWidget>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDropEvent>
#include <QtCore/QUrl>

#include <boost/algorithm/string.hpp>

#include <iostream>


Table::Table( QWidget *parent )
: QTableWidget( parent )
{
	this->setRowCount( 1 );
	//this->setColumnCount(1);

	/*QTableWidgetItem * itemColonne1 = new QTableWidgetItem("Real time");
	this->setHorizontalHeaderItem(0,itemColonne1);*/

	QTableWidgetItem * itemLigne1 = new QTableWidgetItem( "Sequence" );
	this->setVerticalHeaderItem( 0, itemLigne1 );

	this->setEditTriggers( QAbstractItemView::NoEditTriggers );

	this->setAcceptDrops( true );
	this->setDropIndicatorShown( true );
}

void Table::dragEnterEvent( QDragEnterEvent *event )
{
	event->setDropAction( Qt::MoveAction );
	event->accept();
}

void Table::dragMoveEvent( QDragMoveEvent *event )
{
	event->setDropAction( Qt::MoveAction );
	event->accept();
}

void Table::startDrag( Qt::DropActions supportedActions )
{
	std::cout << "TabWidget::startDrag" << std::endl;


	QMimeData *mimeData = new QMimeData;
	mimeData->setText( QString::fromStdString( "timeline" ) );

	Timeline * timeline = &( Projet::getInstance().getTimeline() );
	QList<QUrl> urls;

	BOOST_FOREACH( QModelIndex idx, selectedIndexes() )
	{
		QTableWidgetItem * item = this->itemFromIndex( idx );

                std::string filename = timeline->findCurrentClip( item->column() );
                urls.push_back( QString::fromStdString( filename ) );
	}
	mimeData->setUrls( urls );


	QDrag *drag = new QDrag( this );
	drag->setMimeData( mimeData );


	drag->exec();

}

void Table::dropEvent( QDropEvent *event )
{
	//creation de l'action de drag and drop au sein de la timeline
	ActDragNDropTLToTL actionTlToTl;
	ActDragNDropChutToTL actionChutToTl;


	std::cout << "TableTimeline::dropEvent" << std::endl;
	//on recupere la timeline
	Timeline * timeline = &( Projet::getInstance().getTimeline() );


	//on recupere le mimeData (ce que l'on drag)
	const QMimeData* mimeData = event->mimeData();

	//on recupere la position
	QTableWidgetItem * item = itemAt( event->pos() );
	unsigned int position = item->column();
	std::cout << "y: " << item->column() << std::endl;

	QList<QUrl> urlList = mimeData->urls();

	for( int i = 0; i < urlList.size(); ++i )
	{
		QString text = urlList.at( i ).path();
		std::string filename = text.toStdString();
		std::cout << filename << std::endl;

		if( mimeData->text().toStdString() == "timeline" )
		{
			//timeline->moveElement(filename, position);
			actionTlToTl( filename, position );

		}


		else
		{


			//ajout du clip dans la timeline core
			//timeline->insertClip(filename, position);
			actionChutToTl( filename, position );
		}
	}

	/*std::vector<std::string> filenames;
	boost::algorithm::split( filenames, datas, boost::is_any_of(":") );
	std::cout << "TL: " << filenames.size() << std::endl;*/

	event->acceptProposedAction();


}
