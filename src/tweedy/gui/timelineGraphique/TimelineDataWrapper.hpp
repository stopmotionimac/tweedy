#ifndef TIMELINEDATAWRAPPER_HPP
#define TIMELINEDATAWRAPPER_HPP

#include <QtCore/QObject>

#include <QtDeclarative/QDeclarativeListProperty>

#include "ClipDataWrapper.hpp"

class TimelineDataWrapper : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(int clipRadius READ getClipRadius NOTIFY clipRadiusChanged)
    Q_PROPERTY(QDeclarativeListProperty<ClipDataWrapper> clips READ getClips)
public:
    explicit TimelineDataWrapper(QObject *parent = 0);
    TimelineDataWrapper(const TimelineDataWrapper&){}
    TimelineDataWrapper& operator =(const TimelineDataWrapper&){}
    //int getClipRadius();
    QDeclarativeListProperty<ClipDataWrapper> getClips();

private:
    QList<ClipDataWrapper *> _clips;

};

#endif // TIMELINEDATAWRAPPER_HPP
