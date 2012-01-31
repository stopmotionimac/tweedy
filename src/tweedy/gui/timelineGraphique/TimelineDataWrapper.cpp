#include "TimelineDataWrapper.hpp"

TimelineDataWrapper::TimelineDataWrapper(QObject *parent) :
    QObject(parent)
{
}

//int TimelineDataWrapper::getClipRadius()
//{
//    return 50;
//}

QDeclarativeListProperty<ClipDataWrapper> TimelineDataWrapper::getClips()
{
    return QDeclarativeListProperty<ClipDataWrapper>(this, _clips);
}
