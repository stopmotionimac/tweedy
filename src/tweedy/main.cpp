
#include <QtGui/QApplication>
#include "gui/timesheet/TimeSheet.h"

int main(int argc, char *argv[])
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    
    TimeSheet form;
    form.show();
    
    return app.exec();
}

