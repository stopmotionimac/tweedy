//#include <tweedy/core/Projet.hpp>

#include <tweedy/core/command/GroupeUndoRedoCmd.hpp>
#include <tweedy/core/command/clip/CmdClipSetTimeRange.hpp>

#include <tweedy/gui/Undo/UndoWidget.hpp>
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


      projet->setGphotoInstance();


      /*________TEST AREA_________*/
      //Add a Imedia in projet._mapMedia
      Imedia * clipTest = new Clip("IMAGE.jpg" );
      projet->addImedia(clipTest);

      //make chutier with folder
      projet->makeChutier();

      //print all media on projet
      projet->printAllMedia();

      //TEST to get name from an Imedia


      // affectation de la valeur 15 à l'objet pointé par obj1
      projet->setValue (15);

      // affichage de _value
      //std::cout << "obj1::_value = " << projet->getValue () << std::endl;


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
        
        
        //test undo redo
        
        CommandManager cmdMan;
        Clip c1("img/tweedy0.jpg" );
    
        //test pour une commande
        IUndoRedoCommand * cmd1 = new CmdClipSetTimeRange(c1,"Time Out + 2", 2);
        
        //test pour un groupe de commandes
        IUndoRedoCommand * cmd2 = new CmdClipSetTimeRange(c1,"Time Out - 2", -2);
        IUndoRedoCommand * cmd3 = new CmdClipSetTimeRange(c1,"Time Out + 10", 10);
    
        boost::ptr_vector<IUndoRedoCommand> cmdGr1;
        cmdGr1.push_back(cmd2);
        cmdGr1.push_back(cmd3);
        
        IUndoRedoCommand * grCmd1 = new GroupeUndoRedoCmd(cmdGr1, "Groupe de cmd 1");
        
        //ajout des commandes au command manager
        cmdMan.pushNewCommand(cmd1);
        cmdMan.pushNewCommand(grCmd1);
               
        UndoView* undoView = new UndoView(&cmdMan);
    
        QWidget * undoWidget = new UndoWidget(undoView);
        undoWidget->setWindowTitle("Command List");
        undoWidget->show();
        

	mainWin.show();
	return app.exec();

        // destruction de l'instance unique
        projet->kill ();
}
