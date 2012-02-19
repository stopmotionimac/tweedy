#ifndef TIMELINEGRAPHIQUE_H
#define TIMELINEGRAPHIQUE_H

#include <QtGui/QWidget>
#include <QtDeclarative/QDeclarativeView>

#include "ClipDataWrapper.hpp"
#include "TimelineDataWrapper.hpp"

#include "properties.h"

class TimelineGraphique : public QWidget
{
public:
    TimelineGraphique(QWidget * parent);

    void update();

private:
    TimelineDataWrapper _timelineData;
    ClipDataWrapper _clipData;
    Properties _prop;

    QDeclarativeView* _qmlView;
};

#endif // TIMELINEGRAPHIQUE_H
