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
        //creation of the drag and drop action inside the timeline
	ActDragNDropTLToTL actionTlToTl;
	ActDragNDropChutToTL actionChutToTl;

        //get the timeline
	Timeline * timeline = &( Projet::getInstance().getTimeline() );


        //get the mimeData (what is dragged)
	const QMimeData* mimeData = event->mimeData();

        //get the position
	QTableWidgetItem * item = itemAt( event->pos() );
	unsigned int position = item->column();

	QList<QUrl> urlList = mimeData->urls();

	for( int i = 0; i < urlList.size(); ++i )
	{
		QString text = urlList.at( i ).path();
		std::string filename = text.toStdString();

		if( mimeData->text().toStdString() == "timeline" )
		{
			actionTlToTl( filename, position );
		}

		else
		{
                    //add clip on the core timeline
                    actionChutToTl( filename, position );
		}
	}

	event->acceptProposedAction();
}
