#include "timelinegraphique.h"

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtGui/QVBoxLayout>
#include <QtCore/QUrl>

TimelineGraphique::TimelineGraphique(QWidget * parent):
    QWidget(parent)
{

    /*QDeclarativeView *qmlView = new QDeclarativeView(this);
    qmlView->setSource(QUrl::fromLocalFile("timelineQML.qml"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(qmlView);*/

}
