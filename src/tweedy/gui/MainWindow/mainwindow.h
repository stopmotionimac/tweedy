#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QListWidget>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <tweedy/gui/timesheet/TimeSheet.h>
#include <tweedy/gui/viewerImg/ViewerImg.h>
#include <tweedy/gui/chutier/chutier.h>
#include <tweedy/gui/timeline/TimeLineUi.h>

#include "startwindow.h"
#include "newprojectwindow.h"

#include<tweedy/core/Gphoto/Gphoto.hpp>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        ~MainWindow();

    public Q_SLOTS:
        void on_captureAction_triggered();
        void on_newProjectAction_triggered();
        void on_searchFolderProjectButton_clicked();

    private:
        void createActions();
        void createStartWindow();
        void createMenuBar();
        void createToolBar();
        void createWidgets();
        void createStatusBar();

        void createWidgetViewer();

        QMenu * fileMenu;
        QMenu * editMenu;
        QMenu * viewMenu;
        QMenu * timelineMenu;
        QMenu * paramsMenu;
        QMenu * helpMenu;

        QAction * newProjectAction;
        QAction * openProjectAction;
        QAction * saveProjectAction;
        QAction * quitAction;
        QAction * undoAction;
        QAction * redoAction;
        QAction * aboutAction;
        QAction * aboutQtAction;

        QAction * _captureAction;

        QToolBar * fileToolBar;
        QToolBar * editToolBar;

        QStatusBar * myStatusBar;

        //Widgets de la fenêtre qu'on ajoute en QDockWidget
        TimeSheet* timesheet;
        ViewerImg* viewerImg;
        Chutier* chutier;
        TimeLineUi* timeline;

        StartWindow * startWindowDialog;
        newProjectWindow * newProjectDialog;

        Gphoto * gPhotoInstance;

};

#endif // MAINWINDOW_H
