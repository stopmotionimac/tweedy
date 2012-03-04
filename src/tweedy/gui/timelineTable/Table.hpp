#ifndef _TWEEDY_TABLE_HPP_
#define _TWEEDY_TABLE_HPP_

#include <QtGui/QTableWidget>

class Table : public QTableWidget
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = 0);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent * event);
    void startDrag(Qt::DropActions supportedActions);

};

#endif // TABLETIMELINE_H
