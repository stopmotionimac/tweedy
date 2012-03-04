#include <tweedy/core/Projet.hpp>
#include <tweedy/gui/TweedyApp.hpp>

#include <tweedy/gui/mainWindow/MainWindow.hpp>

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtCore/QFile>

#include <iostream>

int main( int argc, char* argv[] )
{
	//init the Projet's singleton

	// pointeur sur l'unique instance de la classe UniqueObject
	Projet& projet = Projet::getInstance( );

	//projet->setGphotoInstance();

	/*________TEST AREA_________*/
	//Add a Imedia in projet._mapMedia
	//Clip clipTest("IMAGE.jpg" );
	//projet.addImedia(clipTest);

	//USELESS//
	//make chutier with folder
	//projet.makeChutier();

	//print all media on projet
	//projet.printAllMedia();



	/*________TEST AREA_________*/


	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	TweedyApp app( argc, argv );

	MainWindow mainWin;

	// Load css stylesheet
	const QString appCss( QCoreApplication::applicationDirPath( ) + "/resources/tweedy.css" );
	QFile appCssFile( appCss );
	if( !appCssFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
	{
		std::cout << "Failed to open css file: " << appCss.toStdString( ) << std::endl;
	}
	else
	{
		const QString cssContent( appCssFile.readAll( ) );
		//std::cout << "cssContent: " << cssContent.toStdString() << std::endl;
		qApp->setStyleSheet( cssContent );
	}

	//        UndoView* undoView = new UndoView(&projet.getCommandManager());
	//
	//        QWidget* undoWidget = new UndoWidget(undoView);
	//        undoWidget->setWindowTitle("Command List");
	//        undoWidget->show();

	mainWin.show( );
	int res = app.exec( );

	// destruction de l'instance unique
	projet.kill( );

	return res;
}
