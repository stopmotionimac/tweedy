#ifndef _TWEEDY_TIMELINEDATAWRAPPER_HPP_
#define _TWEEDY_TIMELINEDATAWRAPPER_HPP_

#include "ClipDataWrapper.hpp"

#include <tweedy/core/Projet.hpp>

#include <qobjectlistmodel.h>

#include <QtDeclarative/QDeclarativeListProperty>
#include <QtDeclarative/QDeclarativeView>

#include <QtCore/QObject>

class TimelineDataWrapper : public QObject
{
	Q_OBJECT

public:
        Q_PROPERTY( QObjectListModel* clips READ getClips NOTIFY clipsChanged )
	Q_PROPERTY( int maxTime READ getMaxTime NOTIFY maxTimeChanged )
        Q_PROPERTY( int timeMarker READ getTimeMarker NOTIFY timeMarkerChanged )
        Q_PROPERTY( int currentTime READ getCurrentTime NOTIFY currentTimeChanged)

	explicit TimelineDataWrapper( QObject *parent = 0 );

	TimelineDataWrapper( const TimelineDataWrapper& other )
	{
		*this = other;
	}

	TimelineDataWrapper& operator=(const TimelineDataWrapper& other );

	~TimelineDataWrapper( );

        QObjectListModel* getClips(){ return &_clips; }
        Timeline& getTimeline(){ return Projet::getInstance().getTimeline(); }
        const Timeline& getTimeline() const{ return Projet::getInstance().getTimeline(); }
        int getMaxTime() const{ return getTimeline().getMaxTime(); }

        int getTimeMarker() const{ return _timeMarker; }
        int getCurrentTime() const{ return _currentTime; }

        Q_INVOKABLE void displayCurrentClip( int time );
        Q_INVOKABLE int translate( int timeInClipToDrag, int timeToDrop );
	Q_INVOKABLE void displayCursor( QString );
        Q_INVOKABLE int getMarkerPosition( int timeToAdd, bool positiveMove );
        Q_INVOKABLE void displayClip( int time ){ Q_EMIT displayChanged( 0, time ); }
        Q_INVOKABLE void deleteItem();
        Q_INVOKABLE void unselectAll();
        Q_INVOKABLE void selectClip( int timeIn );
        Q_INVOKABLE bool isSelected(int timeIn);
        Q_INVOKABLE void changeTimeInClip(int timeIn, int time);
        Q_INVOKABLE void changeTimeOutClip(int timeIn, int time);
        Q_INVOKABLE void updateListe();


private:
#ifndef Q_MOC_RUN
	boost::signals::scoped_connection _dataConnection;
#endif
        QObjectListModel _clips;
        int _timeMarker;

Q_SIGNALS :
        void clipsChanged( );
        void maxTimeChanged( );
        void timeChanged( int time );
        void enableUpdatesSignal( const bool update );
        void timelineScaleChanged();
        void timeMarkerChanged();
        void currentTimeChanged( int );
        void displayChanged( int unusedValue, int time );

public Q_SLOTS:
        void time(int time) { Q_EMIT timeChanged(time); }


public:
        void coreDataChanged();
        int _currentTime;

private:
        //void updateListe();
};

#endif // TIMELINEDATAWRAPPER_HPP
