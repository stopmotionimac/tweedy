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
#include <QtGui/QTabWidget>

#include "listwidget.h"

class Chutier : public QWidget
{
    Q_OBJECT

public:
    explicit Chutier(QWidget *parent);
    ~Chutier();

    void contextMenuEvent(QContextMenuEvent *event);

public Q_SLOTS:
    void on_photo_selected(/*QListWidgetItem * item*/);
    void on_importAction_triggered();
    void on_deleteAction_triggered();

private:
    ListWidget * _listWidget;

    QToolButton * _importButton;
    QToolButton * _deleteButton;

    QAction * _importAction;
    QAction * _deleteAction;

    QLabel * _viewerChutier;

    QTabWidget * _tabWidget;

public:
    QDockWidget * _viewerChutierDock;

};

#endif // CHUTIER_H
