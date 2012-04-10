#ifndef DropArea_H
#define DropArea_H

#include <QtDeclarative/QDeclarativeItem>
#include <tweedy/core/Timeline.hpp>
#include <tweedy/core/Projet.hpp>


class DropArea : public QDeclarativeItem
{
    Q_OBJECT

public:
    DropArea()
    {
        setAcceptDrops(true);
    }

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    Timeline* getTimeline(){ return &(Projet::getInstance().getTimeline()); }

    Q_INVOKABLE void insertElement( int position );

Q_SIGNALS:
    void dragEnter(int position);
    void dragMove(int position);
    void dragLeave();
    void drop(int position);

private:


};

#endif
