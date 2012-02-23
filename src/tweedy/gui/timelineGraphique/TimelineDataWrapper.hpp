#ifndef TIMELINEDATAWRAPPER_HPP
#define TIMELINEDATAWRAPPER_HPP

#include "ClipDataWrapper.hpp"
#include <tweedy/core/Projet.hpp>

#include <QtDeclarative/QDeclarativeListProperty>
#include <QtDeclarative/QDeclarativeView>

#include <QtCore/QObject>

//Q_DECLARE_METATYPE(QObject*);
//Q_DECLARE_METATYPE(QList<QObject*>);

class TimelineDataWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> clips READ getClips NOTIFY clipsChanged)
    Q_PROPERTY(int maxtime READ getMaxtime NOTIFY maxtimeChanged)


public:
    explicit TimelineDataWrapper(QObject *parent = 0);
    TimelineDataWrapper(const TimelineDataWrapper& other)
    {
        *this = other;
    }
    TimelineDataWrapper& operator=(const TimelineDataWrapper& other)
    {
        _timeInDrag = other._timeInDrag;
        _readyToDrag = other._readyToDrag;
        _clips = other._clips;
        return *this;
    }
    ~TimelineDataWrapper();

    QList<QObject*> getClips();

    Timeline& getTimeline() const { return Projet::getInstance().getTimeline(); }

    int getMaxtime() const { return getTimeline().maxTime(); }

    Q_INVOKABLE void play(int time);

    Q_INVOKABLE void setTimeInDrag(int mousePosition){ _timeInDrag = mousePosition/100 ; _readyToDrag = true;  }
    Q_INVOKABLE void dragNdrop(int mousePosition);

    Q_INVOKABLE void displayCursor(QString);

Q_SIGNALS:
    void fullUpdate();

private:
#ifndef Q_MOC_RUN
    boost::signals::scoped_connection _dataConnection;
#endif
    int _timeInDrag;
    bool _readyToDrag;
    QList<QObject*> _clips;

Q_SIGNALS:
    void clipsChanged();
    void maxtimeChanged();
    void timeChanged(int time);

public Q_SLOTS:
    void updateListe();
};



#endif // TIMELINEDATAWRAPPER_HPP
