#include <tweedy/core/Projet.hpp>

#include <tweedy/gui/timesheet/TimeSheet.h>
#include <tweedy/gui/MainWindow/mainwindow.h>

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtCore/QFile>

#include <iostream>


int main(int argc, char *argv[])
{
    //init the Projet's singleton

    // pointeurs sur l'unique instance de la classe UniqueObject
      Projet * projet;

      // initialisation des pointeurs
      projet = Projet::getInstance ();


      //projet->setGphotoInstance();

      /*________TEST AREA_________*/
      //Add a Imedia in projet._mapMedia
      Imedia * clipTest = new Clip("IMAGE.jpg" );
      //projet->addImedia(clipTest);

      //make chutier with folder
      //projet->makeChutier();

      //print all media on projet
      //projet->printAllMedia();

      //TEST to get name from an Imedia


      // affectation de la valeur 15 à l'objet pointé par obj1
      //projet->setValue (15);

      // affichage de _value
      //std::cout << "obj1::_value = " << projet->getValue () << std::endl;

      //projet->setGphotoInstance();


      /*________TEST AREA_________*/


	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);

        MainWindow mainWin(projet);

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

	mainWin.show();
	return app.exec();

        // destruction de l'instance unique
        projet->kill ();
}
