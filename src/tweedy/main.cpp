
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include "gui/timesheet/TimeSheet.h"
#include "gui/MainWindow/mainwindow.h"

int main(int argc, char *argv[])
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    
    MainWindow mainWin;
    mainWin.show();
    
    return app.exec();
}

