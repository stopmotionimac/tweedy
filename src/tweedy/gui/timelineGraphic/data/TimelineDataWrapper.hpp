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
        //Q_PROPERTY( int timeIn READ getTimeIn NOTIFY timeChanged )
        Q_PROPERTY( int timelineScale READ getTimelineScale WRITE setTimelineScale NOTIFY timelineScaleChanged )
        Q_PROPERTY( int timeMarker READ getTimeMarker NOTIFY timeMarkerChanged )

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
        //int getTimeIn() const{ return _timeInDrag; }
        int getTimelineScale() const{ return _timelineScale; }
        void setTimelineScale(int timelineScale) { _timelineScale = timelineScale; Q_EMIT timelineScaleChanged();  }
        int getTimeMarker() const{ return _timeMarker; }

	Q_INVOKABLE void play( int time );
        Q_INVOKABLE void translate( int timeInClipToDrag, int timeToDrop );
	Q_INVOKABLE void displayCursor( QString );
        Q_INVOKABLE int getMarkerPosition( int timeToAdd, bool positiveMove );

private:
#ifndef Q_MOC_RUN
	boost::signals::scoped_connection _dataConnection;
#endif
        QObjectListModel _clips;
        int _timelineScale;
        int _timeMarker;

Q_SIGNALS:
	void clipsChanged( );
	void maxTimeChanged( );
	void timeChanged( int time );
	void enableUpdatesSignal( const bool update );
        void timelineScaleChanged();
        void timeMarkerChanged();

public:
	void coreDataChanged( );

private:
	void updateListe( );
};



#endif // TIMELINEDATAWRAPPER_HPP
