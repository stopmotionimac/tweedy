/*
 * File:   main.cpp
 * Author: Julien
 *
 * Created on 5 novembre 2011, 23:40
 */

#include <QtGui/QApplication>
#include "HelloForm.h"

int main(int argc, char *argv[])
{
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    HelloForm form;
    form.show();
    
    return app.exec();
}

