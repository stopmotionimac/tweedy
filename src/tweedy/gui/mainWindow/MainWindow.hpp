#ifndef _TWEEDY_MAINWINDOW_HPP_
#define _TWEEDY_MAINWINDOW_HPP_

#include "StartWindow.hpp"
#include "NewProjectWindow.hpp"

#include <tweedy/core/gphoto/Gphoto.hpp>
#include <tweedy/core/Projet.hpp>

#include <tweedy/gui/viewerImg/ViewerTweedy.hpp>
#include <tweedy/gui/chutier/Chutier.hpp>
#include <tweedy/gui/timelineTable/TimelineTable.hpp>
#include <tweedy/gui/undo/UndoWidget.hpp>
#include <tweedy/gui/undo/UndoView.hpp>
#include <tweedy/gui/timelineGraphic/TimelineGraphic.hpp>
#include <tweedy/gui/configCamera/ConfigCamera.hpp>
#include <tweedy/gui/aboutTweedy/AboutTweedy.hpp>
#include <tweedy/gui/configCamera/ConfigCamera.hpp>
#include <tweedy/gui/ExportWidget/ExportWidget.hpp>

#include <QtGui/QMainWindow>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>

#include <QtCore/QTimer>

class MainWindow : public QMainWindow
{
        Q_OBJECT

public:
        MainWindow();
        ~MainWindow();

        QAction * getPlayPauseAction()
        {
                return _playPauseAction;
        }

        QAction * getNextAction()
        {
                return _nextAction;
        }

        QAction * getPreviousAction()
        {
                return _prevAction;
        }

        QAction * getRetour0Action()
        {
                return _zeroAction;
        }

        Timeline& getTimeline()
        {
                return Projet::getInstance().getTimeline();
        }
        int getFps(){ return _fps; }
        unsigned int time() { return _time; }

public Q_SLOTS:
        
        std::string generateTimeData(int, int, int);

        void on_captureAction_triggered();
        void on_newProjectAction_triggered();
        void on_searchFolderProjectButton_clicked();
        void on_openProjectAction_triggered();
        void on_saveAsProjectAction_triggered();
        void on_undoButton_clicked();
        void on_redoButton_clicked();
        void writeTime( int newValue );
        void on_close_window();
        void on_saveProjectAction_triggered();
        void on_loadProjectAction_triggered(const char*);
        void on_aboutAction_triggered();
        void on_configAction_triggered();
        void on_acceptedNewProjectWindow();
        void on_exportAction_triggered();

        void handle_playPauseAction_triggered();
        void handle_zeroAction_triggered();
        void handle_nextAction_triggered();
        void handle_prevAction_triggered();

        void increaseTime();
        void changeFps( int value ) { _fps = value; }

Q_SIGNALS:
        void timeChanged( int newValue );
        void displayChanged( std::string filename );

private:
        Projet& project()
        {
                return Projet::getInstance();
        }
        void createActions();
        void createStartWindow();
        void createMenuBar();
        void createToolBar();
        void createWidgets();
        void createStatusBar();

        void createWidgetViewer();

        QMenu* _fileMenu;
        QMenu* _editMenu;
        QMenu* _viewMenu;
        QMenu* _timelineMenu;
        QMenu* _paramsMenu;
        QMenu* _helpMenu;

        QAction* _newProjectAction;
        QAction* _openProjectAction;
        QAction* _saveProjectAction;
        QAction* _saveAsProjectAction;
        QAction* _quitAction;
        QAction* _undoAction;
        QAction* _redoAction;
        QAction* _configAction;
        QAction* _aboutAction;
        QAction* _aboutQtAction;

        QAction* _captureAction;
        QAction* _exportAction;

        QAction* _playPauseAction;
        QAction* _nextAction;
        QAction* _prevAction;
        QAction* _zeroAction;

        QToolBar* _fileToolBar;
        QToolBar* _editToolBar;

        QStatusBar* _statusBar;

        bool _isPlaying;
        QTimer* _timer;
        int _fps;
        int _time;

        /// @brief Widgets de la fenêtre qu'on ajoute en QDockWidget
        /// @{
        ViewerTweedy* _viewerImg;
        Chutier* _chutier;
        UndoView* _undoView;
        QWidget* _undoWidget;
        TimelineGraphic* _timelineGraphic;
        ConfigCamera* _configCamera;
        ExportWidget* _exportWidget;
        /// @}

        /// @brief Modal widgets
        /// @{
        StartWindow* _startWindowDialog;
        newProjectWindow* _newProjectDialog;
        AboutTweedy* _aboutWindow;
        /// @}
};

#endif
