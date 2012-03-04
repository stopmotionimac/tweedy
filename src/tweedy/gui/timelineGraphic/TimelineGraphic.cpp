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
	//    _qmlView->rootContext()->setContextProperty( "clipsData", &_timelineData.getClips() );
	_qmlView->setSource( QUrl::fromLocalFile( _timelineQmlFile ) );

	_qmlView->setResizeMode( QDeclarativeView::SizeRootObjectToView );
	_qmlView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate ); // test

	//    qmlRegisterType<ClipDataWrapper>("MyClipData",1,0,"ClipData");
	//    qmlRegisterType<TimelineDataWrapper>("MyTimelineData",1,0,"TimelineData");

	//    QList<QObject *> dataList;
	//    dataList.append(new ClipDataWrapper());
	//    dataList.append(new ClipDataWrapper());
	//    dataList.append(new ClipDataWrapper());

	//    _qmlView->rootContext()->setContextProperty("tweedyTimelineData",QVariant::fromValue(dataList));

	QVBoxLayout *layout = new QVBoxLayout( this );
	layout->addWidget( _qmlView );

	_qmlFileWatcher.addPath( _timelineQmlFile );
	connect( &_qmlFileWatcher, SIGNAL( fileChanged( const QString & ) ), this, SLOT( onQmlFileChanged( const QString & ) ) );
}

void TimelineGraphic::onQmlFileChanged( const QString &file )
{
	std::cout << "TimelineGraphique::onQmlFileChanged: " << file.toStdString() << std::endl;
	_qmlView->setSource( QUrl::fromLocalFile(file) );
	_qmlView->update();
	_qmlView->repaint();
//	updateTweedyDatas();
}
