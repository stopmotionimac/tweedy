#ifndef TABLETIMELINE_H
#define TABLETIMELINE_H

#include <QtGui/QTableWidget>

class TableTimeline : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableTimeline(QWidget *parent = 0);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent * event);
    void startDrag(Qt::DropActions supportedActions);

};

#endif // TABLETIMELINE_H
