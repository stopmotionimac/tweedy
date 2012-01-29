#include "timelinegraphique.h"

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeProperty>
#include <QtGui/QVBoxLayout>
#include <QtCore/QUrl>

#include <iostream>

TimelineGraphique::TimelineGraphique(QWidget * parent):
    QWidget(parent)
{

    QDeclarativeView *qmlView = new QDeclarativeView(this);
    qmlView->setSource(QUrl::fromLocalFile("src/tweedy/gui/timelineGraphique/timelineQML.qml"));

    qmlView->rootContext()->setContextProperty("aaa", &_prop);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(qmlView);

//    // get root object
//    QObject * rootObject = dynamic_cast<QObject *>(qmlView->rootObject());

//    // find element by name
//    QObject * timeline = rootObject->findChild<QObject *>(QString("timeline"));


}
