#include "TimelineDataWrapper.hpp"

TimelineDataWrapper::TimelineDataWrapper(QObject *parent) :
    QObject(parent)
{
    for(int i=0;i<10;i++)
        _clips.push_back( new ClipDataWrapper() );
}

//int TimelineDataWrapper::getClipRadius()
//{
//    return 50;
//}

QList<QObject*> TimelineDataWrapper::getClips()
{
    return _clips;
}

int TimelineDataWrapper::getSizeClips()
{
    return _clips.size();
}
