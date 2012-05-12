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

	Projet& projet = Projet::getInstance( );

	TweedyApp app( argc, argv );

	MainWindow mainWin;

	// Load css stylesheet
	const QString appCss( QCoreApplication::applicationDirPath( ) + "/resources/tweedy.css" );
	QFile appCssFile( appCss );
	if( !appCssFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
	{
                //std::cout << "Failed to open css file: " << appCss.toStdString( ) << std::endl;
	}
	else
	{
		const QString cssContent( appCssFile.readAll( ) );
		qApp->setStyleSheet( cssContent );
	}

	mainWin.show( );
	int res = app.exec( );

        //destruction of the unique instance
	projet.kill( );

	return res;
}
