
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

#include "mainwidget.h"

int main(int argc, char** argv)
{
    QApplication a (argc, argv);

    MainWidget* mainWidget=new MainWidget();
    mainWidget->show();
    int r=0;
    try
    {
	r=a.exec();
    }catch (...)
    {
	QMessageBox::critical(NULL, QObject::tr("Error"), QObject::tr("Critical error - Unhandled exception in the application!"));
	r=-1;
    }
    delete mainWidget;
    return r;
}

