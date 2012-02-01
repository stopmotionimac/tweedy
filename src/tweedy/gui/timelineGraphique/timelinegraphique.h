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
    Properties _prop;
    TimelineDataWrapper _timelineData;
    ClipDataWrapper _clipData;

    QDeclarativeView* _qmlView;
};

#endif // TIMELINEGRAPHIQUE_H
