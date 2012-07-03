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
, _qmlFileWatcher( this )
{
    _dropArea = new DropArea();

    qmlRegisterType<QObjectListModel>();
    qmlRegisterType<DropArea>("DragNDrop", 1, 0, "DropArea");

    this->rootContext()->setContextProperty( "_tw_graphicTimeline", this );
    this->rootContext()->setContextProperty( "_tw_timelineData", &_timelineData );
    this->rootContext()->setContextProperty( "_tw_dropArea", _dropArea );

    this->setSource( QUrl::fromLocalFile( _timelineQmlFile ) );
    this->setResizeMode( QDeclarativeView::SizeRootObjectToView );

    _qmlFileWatcher.addFile( this->source(), true);

    /*QObject contentView = this->rootObject().findChild<QObject>(QString("_tw_timelineData"));
    QObject::connect(&_timelineData, SIGNAL(timeChanged(int)), contentView, SLOT(updateViewWithItem(QString)));
    QObject *rootObject = dynamic_cast<QObject*>(view.rootObject());*/

    connect( &_timelineData, SIGNAL( enableUpdatesSignal( const bool ) ), this, SLOT( onEnableUpdates( const bool ) ) );

}

void TimelineGraphic::onEnableUpdates( const bool update )
{
    this->setUpdatesEnabled( update );
}

TimelineGraphic::~TimelineGraphic(){
    delete _dropArea;

}
