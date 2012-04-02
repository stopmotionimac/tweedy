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

#include <QtGui/QMainWindow>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();
        void resizeEvent( QResizeEvent * event );

public Q_SLOTS:
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
	void on_loadProjectAction_triggered();
	void on_aboutAction_triggered();
	void on_acceptedNewProjectWindow();

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
	QAction* _aboutAction;
	QAction* _aboutQtAction;

	QAction* _captureAction;

	QToolBar* _fileToolBar;
	QToolBar* _editToolBar;

	QStatusBar* _statusBar;

	/// @brief Widgets de la fenêtre qu'on ajoute en QDockWidget
	/// @{
	ViewerTweedy* _viewerImg;
	Chutier* _chutier;
	TimelineTable* _timelineTable;
	UndoView* _undoView;
	QWidget* _undoWidget;
	TimelineGraphic* _timelineGraphic;
	ConfigCamera* _configCamera;
	/// @}

	/// @brief Modal widgets
	/// @{
	StartWindow* _startWindowDialog;
	newProjectWindow* _newProjectDialog;
	AboutTweedy* _aboutWindow;
	/// @}
};

#endif
