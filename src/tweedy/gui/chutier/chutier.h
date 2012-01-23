#ifndef CHUTIER_H
#define CHUTIER_H

#include <QtGui/QWidget>
#include <QtGui/QToolButton>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QAction>
#include <QtGui/QDockWidget>
#include <QtGui/QContextMenuEvent>

#include "listwidget.h"

class Chutier : public QWidget
{
    Q_OBJECT

public:
    explicit Chutier(QWidget *parent = 0);
    ~Chutier();

    void contextMenuEvent(QContextMenuEvent *event);

public Q_SLOTS:
    void on_photo_selected(QListWidgetItem * item);
    void on_importAction_triggered();
    void on_deleteAction_triggered();

private:
    ListWidget * listWidget;

    QToolButton * importButton;
    QToolButton * deleteButton;

    QAction * importAction;
    QAction * deleteAction;

    QLabel * viewerChutier;

public:
    QDockWidget * viewerChutierDock;

};

#endif // CHUTIER_H
