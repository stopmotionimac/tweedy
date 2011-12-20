#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QListWidget>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include "../timesheet/TimeSheet.h"
#include "../viewerImg/ViewerImg.h"
#include "../chutier/chutier.h"
#include "../timeline/TimeLine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        ~MainWindow();


    private:
        void createActions();
        void createMenuBar();
        void createToolBar();
        void createWidgets();
        void createStatusBar();

        QMenu * fileMenu;
        QMenu * editMenu;
        QMenu * viewMenu;
        QMenu * timelineMenu;
        QMenu * helpMenu;

        QAction * newAction;
        QAction * openAction;
        QAction * saveAction;
        QAction * quitAction;
        QAction * undoAction;
        QAction * redoAction;
        QAction * aboutAction;
        QAction * aboutQtAction;

        QToolBar * fileToolBar;
        QToolBar * editToolBar;

        QStatusBar * myStatusBar;

        //Widgets de la fenêtre qu'on ajoute en QDockWidget
        TimeSheet* timesheet;
        ViewerImg* viewerImg;
        Chutier* chutier;
        TimeLine* timeline;

};

#endif // MAINWINDOW_H
