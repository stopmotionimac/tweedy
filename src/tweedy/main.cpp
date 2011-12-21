#include "core/Application.hpp"
#include "core/UndoRedoCommand.hpp"

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtCore/QFile>
#include <iostream>

#include "gui/timesheet/TimeSheet.h"
#include "gui/MainWindow/mainwindow.h"


int main(int argc, char *argv[])
{
<<<<<<< HEAD

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
	const QString appCss( QCoreApplication::applicationDirPath() + "/styleSheet.css" );
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

	mainWin.show();
	return app.exec();
}

