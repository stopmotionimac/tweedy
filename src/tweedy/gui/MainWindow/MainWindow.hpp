 #ifndef MAINWINDOW_HPP
 #define MAINWINDOW_HPP

#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QAction>
#include <QtGui/QMenu>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QDockWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QMenuBar>

#include "../timesheet/TimeSheet.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		MainWindow();

	public Q_SLOTS:
		void colorChanged();
		void open();
		void about();
		
		

	private:
		void loadFile(const QString &fileName);

		void createActions();

		void createMenus();
		void createToolBars();
		void createWindow();
		void createStatusBar();
		
		QTextEdit *textEdit;		

		QMenu *_fileMenu;
		QMenu *_editMenu;
		QMenu *_viewMenu;
		QMenu *_TimelineMenu;
		QMenu *_helpMenu;

		QToolBar *_fileToolBar;
		QToolBar *_editToolBar;

		QPushButton *_button1;
		QPushButton *_button2;

		QTabWidget *_videoWidget;

		QWidget * _centralWidget;

		QStatusBar *_statusBar;

		QAction *_newAction;
		QAction *_openAction;
		QAction *_saveAction;
		QAction *_quitAction;
		QAction *_undoAction;
		QAction *_doAction;
		QAction *_aboutAction;
		QAction *_aboutQtAction;
		
                ViewerImg* viewerImg;
                TimeSheet* timesheet;
};



 #endif
