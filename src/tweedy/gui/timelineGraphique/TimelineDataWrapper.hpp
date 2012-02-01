#ifndef TIMELINEDATAWRAPPER_HPP
#define TIMELINEDATAWRAPPER_HPP

#include <QtCore/QObject>

#include <QtDeclarative/QDeclarativeListProperty>

#include "ClipDataWrapper.hpp"

//Q_DECLARE_METATYPE(QObject*);
//Q_DECLARE_METATYPE(QList<QObject*>);

class TimelineDataWrapper : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(int clipRadius READ getClipRadius NOTIFY clipRadiusChanged)
    Q_PROPERTY(QList<QObject *> clips READ getClips NOTIFY clipsChanged)
public:
    explicit TimelineDataWrapper(QObject *parent = 0);
    TimelineDataWrapper(const TimelineDataWrapper&){}
    TimelineDataWrapper& operator =(const TimelineDataWrapper&){}
    //int getClipRadius();
    QList<QObject*> getClips();
    //Q_INVOKABLE ClipDataWrapper* getClip(int i) { return &_clips[i]; }
    Q_INVOKABLE int getSizeClips();

private:
    QList<QObject*> _clips;

Q_SIGNALS:
    void clipsChanged();

};



#endif // TIMELINEDATAWRAPPER_HPP
