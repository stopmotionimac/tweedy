#ifndef TIMELINEDATAWRAPPER_HPP
#define TIMELINEDATAWRAPPER_HPP

#include <QtCore/QObject>
#include <tweedy/core/Projet.hpp>

#include <QtDeclarative/QDeclarativeListProperty>

#include "ClipDataWrapper.hpp"

//Q_DECLARE_METATYPE(QObject*);
//Q_DECLARE_METATYPE(QList<QObject*>);

class TimelineDataWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> clips READ getClips NOTIFY clipsChanged)
    Q_PROPERTY(int maxtime READ getMaxtime NOTIFY maxtimeChanged)


public:
    explicit TimelineDataWrapper(QObject *parent = 0);
    TimelineDataWrapper(const TimelineDataWrapper&){}
    TimelineDataWrapper& operator =(const TimelineDataWrapper&){}

    QList<QObject*> getClips();
    int getMaxtime(){ return _timelineCore->maxTime(); }

    Q_INVOKABLE void setTimeInDepart(int timeInDepart){ std::cout << "settimein" << std::endl; _timeInDepart = timeInDepart; }
    Q_INVOKABLE void dragNdrop(int timeInArrivee);

private:
    QList<QObject*> _clips;
    Timeline * _timelineCore;
    int _timeInDepart;

Q_SIGNALS:
    void clipsChanged();
    void maxtimeChanged();
};



#endif // TIMELINEDATAWRAPPER_HPP
