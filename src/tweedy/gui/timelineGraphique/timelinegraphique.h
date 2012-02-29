#ifndef TIMELINEGRAPHIQUE_H
#define TIMELINEGRAPHIQUE_H

#include <QtGui/QWidget>
#include <QtDeclarative/QDeclarativeView>

#include "ClipDataWrapper.hpp"
#include "TimelineDataWrapper.hpp"

class TimelineGraphique : public QWidget
{
    Q_OBJECT
public:
    TimelineGraphique(QWidget * parent);

    TimelineDataWrapper* getTimelineDataWrapper() { return &_timelineData; }

public Q_SLOTS:
    void updateTweedyDatas();

private:
    TimelineDataWrapper _timelineData;

    QDeclarativeView* _qmlView;
};

#endif // TIMELINEGRAPHIQUE_H
