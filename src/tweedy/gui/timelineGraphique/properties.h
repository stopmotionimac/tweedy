#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QtCore/QObject>
#include <QtDeclarative/qdeclarative.h>

#include "TimelineDataWrapper.hpp"

class Properties : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int clipRadius READ getClipRadius NOTIFY clipRadiusChanged)
    //Q_PROPERTY(QObject timelineData READ getTimelineData NOTIFY timelineDataChanged)
public:
    explicit Properties(QObject *parent = 0);
    //Properties& operator =(const Properties&){}
    Q_INVOKABLE void afficheCurseur(QString);
    Q_INVOKABLE void afficheXClip(qreal);
    Q_INVOKABLE void update();
    Q_INVOKABLE int getClipRadius();
    Q_INVOKABLE TimelineDataWrapper getTimelineData();

private:
    TimelineDataWrapper _timelineDataWrapper;

Q_SIGNALS:
    void clipRadiusChanged();
    void timelineDataChanged();

};

#endif // PROPERTIES_H
