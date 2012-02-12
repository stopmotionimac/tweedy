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

    _qmlView = new QDeclarativeView(this);
    _qmlView->setSource(QUrl::fromLocalFile("src/tweedy/gui/timelineGraphique/timelineQML.qml"));

//    _qmlView->rootContext()->setContextProperty("Prop", &_prop);

    _qmlView->rootContext()->setContextProperty("clipData",&_clipData);
    _qmlView->rootContext()->setContextProperty("timelineData",&_timelineData);

    _qmlView->setResizeMode(QDeclarativeView::SizeRootObjectToView);

//    qmlRegisterType<ClipDataWrapper>("MyClipData",1,0,"ClipData");
//    qmlRegisterType<TimelineDataWrapper>("MyTimelineData",1,0,"TimelineData");

//    QList<QObject *> dataList;
//    dataList.append(new ClipDataWrapper());
//    dataList.append(new ClipDataWrapper());
//    dataList.append(new ClipDataWrapper());

//    _qmlView->rootContext()->setContextProperty("timelineData",QVariant::fromValue(dataList));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(_qmlView);


}


void TimelineGraphique::update()
{

}
