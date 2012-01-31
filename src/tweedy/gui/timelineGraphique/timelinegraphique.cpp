#include "timelinegraphique.h"

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeProperty>
#include <QtGui/QVBoxLayout>
#include <QtCore/QUrl>

#include "ClipDataWrapper.hpp"
#include "TimelineDataWrapper.hpp"

#include <iostream>

TimelineGraphique::TimelineGraphique(QWidget * parent):
    QWidget(parent)
{
    _qmlView = new QDeclarativeView(this);
    _qmlView->setSource(QUrl::fromLocalFile("src/tweedy/gui/timelineGraphique/timelineQML.qml"));

    _qmlView->rootContext()->setContextProperty("Prop", &_prop);

    qmlRegisterType<TimelineDataWrapper>("MyTimelineData",1,0,"TimelineData");
    qmlRegisterType<ClipDataWrapper>("MyClipData",1,0,"ClipData");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(_qmlView);

}


void TimelineGraphique::update()
{

}
