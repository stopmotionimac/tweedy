#include "core/Application.hpp"

#include <tweedy/gui/Undo/UndoWidget.hpp>

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtCore/QFile>
#include <iostream>

#include "gui/timesheet/TimeSheet.h"
#include "gui/MainWindow/mainwindow.h"


int main(int argc, char *argv[])
{
    //init the Application's singleton

    // pointeurs sur l'unique instance de la classe UniqueObject
      Application * application;

      // initialisation des pointeurs
      application =Application::getInstance ();

      // affectation de la valeur 15 à l'objet pointé par obj1
      application->setValue (15);

      // affichage de _value
      std::cout << "obj1::_value = " << application->getValue () << std::endl;

      // destruction de l'instance unique
      application->kill ();

	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);
	MainWindow mainWin;

	// Load css stylesheet
	const QString appCss( QCoreApplication::applicationDirPath() + "/resources/tweedy.css" );
	QFile appCssFile( appCss );
	if( ! appCssFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
	{
		std::cout << "Failed to open css file: " << appCss.toStdString() << std::endl;
	}
	else
	{
		const QString cssContent( appCssFile.readAll() );
		//std::cout << "cssContent: " << cssContent.toStdString() << std::endl;
		qApp->setStyleSheet(cssContent);
	}
        
        
        //test undo redo
        
        CommandManager cmdMan ;
    
        IUndoRedoCommand* addCmd1 = new AddCommand(2,"AddCommand1(+2)",cmdMan.getSomme());
        IUndoRedoCommand* dltCmd1 = new DeleteCommand(4,"DeleteCommand1(-4)",cmdMan.getSomme());
        IUndoRedoCommand* addCmd2 = new AddCommand(20,"AddCommand2(+20)",cmdMan.getSomme());
        IUndoRedoCommand* dltCmd2 = new DeleteCommand(1,"DeleteCommand2(-1)",cmdMan.getSomme());
        
        
        cmdMan.pushNewCommand(addCmd1);
        cmdMan.pushNewCommand(dltCmd1);
        cmdMan.pushNewCommand(addCmd2);
        
        cmdMan.undo();
    
        cmdMan.pushNewCommand(dltCmd2);
        
        UndoView* undoView = new UndoView(&cmdMan);
    
        QWidget * undoWidget = new UndoWidget(undoView);
        undoWidget->setWindowTitle("Command List");
        undoWidget->show();

	mainWin.show();
	return app.exec();
}
