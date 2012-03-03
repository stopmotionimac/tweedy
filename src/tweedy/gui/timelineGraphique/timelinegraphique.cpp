#include "timelinegraphique.h"

#include <qobjectlistmodel.h>

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeProperty>
#include <QtGui/QVBoxLayout>
#include <QtCore/QUrl>

#include <iostream>

TimelineGraphique::TimelineGraphique(QWidget * parent)
    : QWidget(parent)
, _timelineQmlFile( "src/tweedy/gui/timelineGraphique/timelineQML.qml" )
{
    std::cout << "TimelineGraphique::TimelineGraphique" << std::endl;
	qmlRegisterType<QObjectListModel>();
	
    _qmlView = new QDeclarativeView(this);

    _qmlView->rootContext()->setContextProperty( "tweedyTimelineData", &_timelineData );
//    _qmlView->rootContext()->setContextProperty( "clipsData", &_timelineData.getClips() );
    _qmlView->setSource(QUrl::fromLocalFile(_timelineQmlFile));

    _qmlView->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    _qmlView->setViewportUpdateMode( QGraphicsView::FullViewportUpdate ); // test

//    qmlRegisterType<ClipDataWrapper>("MyClipData",1,0,"ClipData");
//    qmlRegisterType<TimelineDataWrapper>("MyTimelineData",1,0,"TimelineData");

//    QList<QObject *> dataList;
//    dataList.append(new ClipDataWrapper());
//    dataList.append(new ClipDataWrapper());
//    dataList.append(new ClipDataWrapper());

//    _qmlView->rootContext()->setContextProperty("tweedyTimelineData",QVariant::fromValue(dataList));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(_qmlView);

    connect( &_timelineData, SIGNAL( fullUpdate() ), this, SLOT( updateTweedyDatas() ) );
	
	
	_qmlFileWatcher.addPath( _timelineQmlFile );
	connect( &_qmlFileWatcher, SIGNAL(fileChanged(const QString &)), this, SLOT(onQmlFileChanged(const QString &)) );
}


void TimelineGraphique::updateTweedyDatas()
{
    std::cout << "TimelineGraphique::updateTweedyDatas a" << std::endl;
    _qmlView->rootContext()->setContextProperty("tweedyTimelineData",&_timelineData);
    std::cout << "TimelineGraphique::updateTweedyDatas end" << std::endl;
}


void TimelineGraphique::onQmlFileChanged( const QString &file )
{
//    std::cout << "TimelineGraphique::onQmlFileChanged: " << file.toStdString() << std::endl;
//    _qmlView->setSource( QUrl::fromLocalFile(file) );
//	_qmlView->update();
//	_qmlView->repaint();
//	updateTweedyDatas();
}
