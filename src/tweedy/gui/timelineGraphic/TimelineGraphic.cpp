#include "TimelineGraphic.hpp"

#include <qobjectlistmodel.h>

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeProperty>
#include <QtGui/QVBoxLayout>
#include <QtCore/QUrl>

#include <iostream>


TimelineGraphic::TimelineGraphic( QWidget * parent )
: QWidget( parent )
, _timelineQmlFile( "src/tweedy/gui/timelineGraphic/qml/TW_Timeline.qml" )
{
	std::cout << "TimelineGraphique::TimelineGraphique" << std::endl;
	qmlRegisterType<QObjectListModel>();

	_qmlView = new QDeclarativeView( this );
	_qmlView->rootContext()->setContextProperty( "_tw_timelineData", &_timelineData );
	_qmlView->setSource( QUrl::fromLocalFile( _timelineQmlFile ) );
	_qmlView->setResizeMode( QDeclarativeView::SizeRootObjectToView );
	connect( &_timelineData, SIGNAL( enableUpdatesSignal( const bool ) ), this, SLOT( onEnableUpdates( const bool ) ) );

	QVBoxLayout *layout = new QVBoxLayout( this );
	layout->addWidget( _qmlView );

	_qmlFileWatcher.addPath( _timelineQmlFile );
	connect( &_qmlFileWatcher, SIGNAL( fileChanged( const QString & ) ), this, SLOT( onQmlFileChanged( const QString & ) ) );
	
}


void TimelineGraphic::onEnableUpdates( const bool update )
{
	std::cout << "TimelineGraphique::onEnableUpdates: " << update << std::endl;
	_qmlView->setUpdatesEnabled( update );
}

void TimelineGraphic::onQmlFileChanged( const QString &file )
{
	std::cout << "TimelineGraphique::onQmlFileChanged: " << file.toStdString() << std::endl;
	_qmlView->setSource( QUrl::fromLocalFile(file) );
	_qmlView->rootContext()->setContextProperty( "_tw_timelineData", &_timelineData );
	_qmlView->update();
	_qmlView->repaint();
}
