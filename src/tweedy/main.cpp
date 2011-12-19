#include "core/UndoRedoCommand.hpp"


#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtCore/QFile>
#include "gui/timesheet/TimeSheet.h"
#include "gui/MainWindow/mainwindow.h"
#include "gui/styleSheet.css"


#include <iostream>

int main(int argc, char *argv[])
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    
    QString cssContent( QFile("gui/styleSheet.css").readAll() );
    qApp->setStyleSheet(cssContent);

    MainWindow mainWin;
    mainWin.show();
    return app.exec();   
   
}

