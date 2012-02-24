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
    QLabel * getViewerChutier() { return _viewerChutier; }

    void contextMenuEvent(QContextMenuEvent *event);
    ListWidget& getListWidgetCapture(){ return *_listWidgetCapture; }
    QTabWidget& getTabWidget() { return *_tabWidget; }

public Q_SLOTS:
    void on_photo_selected_import();
    void on_photo_selected_capture();
    void on_importAction_triggered();
    void on_deleteAction_triggered();
    void changedPixmap(int row, int column);

private:
    ListWidget * _listWidgetImport;
    ListWidget * _listWidgetCapture;

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
