#include <QtGui/QGraphicsSceneDragDropEvent>
#include <QtCore/QMimeData>
#include "DropArea.hpp"
#include <tweedy/core/action/ActDragNDropChutToTL.hpp>


void DropArea::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
    event->acceptProposedAction();

    Q_EMIT dragEnter(event->pos().x());

}

void DropArea::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
    event->acceptProposedAction();

    Q_EMIT dragMove(event->pos().x());

}

void DropArea::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_EMIT dragLeave();
}


void DropArea::dropEvent(QGraphicsSceneDragDropEvent *event)
{

    event->setAccepted(true);
    event->acceptProposedAction();
    Timeline* t = getTimeline();

    for (int i=0; i<event->mimeData()->urls().size(); ++i)
        t->setUrlList(event->mimeData()->urls().at( i ).path().toStdString());

    Q_EMIT drop(event->pos().x());
}



void DropArea::insertElement( int position )
{
    ActDragNDropChutToTL actionChutToTl;
    Timeline* t = getTimeline();

    for( int i = 0; i < t->getUrlList().size(); ++i )
        actionChutToTl( t->getUrlList().at( i ), position );

    t->clearUrlList();
}
