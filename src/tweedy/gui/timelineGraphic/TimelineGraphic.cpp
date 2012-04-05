#include "TimelineGraphic.hpp"

#include <qobjectlistmodel.h>

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeProperty>
#include <QtGui/QVBoxLayout>
#include <QtCore/QUrl>

#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDropEvent>

#include <tweedy/core/action/ActDragNDropChutToTL.hpp>

#include <iostream>


TimelineGraphic::TimelineGraphic( QWidget * parent )
: QDeclarativeView( parent )

, _timelineQmlFile( "src/tweedy/gui/timelineGraphic/qml/TW_Timeline.qml" )
{
    _dropArea = new DropArea();

    std::cout << "TimelineGraphique::TimelineGraphique" << std::endl;
        qmlRegisterType<QObjectListModel>();


        this->rootContext()->setContextProperty( "_tw_graphicTimeline", this );
	this->rootContext()->setContextProperty( "_tw_timelineData", &_timelineData );
        this->rootContext()->setContextProperty( "_tw_dropArea", _dropArea );

	this->setSource( QUrl::fromLocalFile( _timelineQmlFile ) );
        this->setResizeMode( QDeclarativeView::SizeRootObjectToView );

	connect( &_timelineData, SIGNAL( enableUpdatesSignal( const bool ) ), this, SLOT( onEnableUpdates( const bool ) ) );

	_qmlFileWatcher.addPath( _timelineQmlFile );
	connect( &_qmlFileWatcher, SIGNAL( fileChanged( const QString & ) ), this, SLOT( onQmlFileChanged( const QString & ) ) );
}



void TimelineGraphic::dragEnterEvent(QDragEnterEvent *event)
{
    event->setAccepted(true);

     //on recupere le mimeData (ce que l'on drag)
     const QMimeData* mimeData = event->mimeData();

     _dropArea->setDropPosition(event->pos().x());
     setUrlList(mimeData->urls());

     event->acceptProposedAction();

}


 void TimelineGraphic::dropEvent(QDropEvent *event)
{

}

void TimelineGraphic::insertElement( int position )
 {
     ActDragNDropChutToTL actionChutToTl;

     std::cout << "TableTimeline::dropEvent" << std::endl;

     for( int i = 0; i < _urlList.size(); ++i )
     {
             QString text = _urlList.at( i ).path();
             std::string filename = text.toStdString();

             actionChutToTl( filename, position );
     }

 }


void TimelineGraphic::onEnableUpdates( const bool update )
{
	std::cout << "TimelineGraphique::onEnableUpdates: " << update << std::endl;
	this->setUpdatesEnabled( update );
}

void TimelineGraphic::onQmlFileChanged( const QString &file )
{
	std::cout << "TimelineGraphique::onQmlFileChanged: " << file.toStdString() << std::endl;
	this->setSource( QUrl::fromLocalFile(file) );
	this->rootContext()->setContextProperty( "_tw_timelineData", &_timelineData );
	this->update();
	this->repaint();
}

TimelineGraphic::~TimelineGraphic(){
    delete _dropArea;

}
