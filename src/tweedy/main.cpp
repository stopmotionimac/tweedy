#include "core/Application.hpp"
#include "core/UndoRedoCommand.hpp"

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtCore/QFile>

#include "gui/timesheet/TimeSheet.h"
#include "gui/MainWindow/mainwindow.h"


#include <iostream>

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

    QString appPath( QCoreApplication::applicationDirPath() + "/styleSheet.css" );
    std::cout << "appPath: " << appPath.toStdString() << std::endl;
    QString cssContent( QLatin1String( QFile(appPath).readAll() ) );
    //std::cout << "cssContent: " << cssContent.latin1() << std::endl;
    qApp->setStyleSheet(cssContent);

    mainWin.show();
    return app.exec();   
   
}

