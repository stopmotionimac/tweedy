#ifndef LISTWIDGET_H
#define LISTWIDGET_H


#include <QtGui/QListWidget>


class ListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ListWidget(QWidget *parent = 0);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


private:

};

#endif // LISTWIDGET_H
