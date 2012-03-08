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
    Q_PROPERTY( int timeIn READ getTimeIn NOTIFY timeChanged )

	explicit TimelineDataWrapper( QObject *parent = 0 );

	TimelineDataWrapper( const TimelineDataWrapper& other )
	{
		*this = other;
	}

	TimelineDataWrapper& operator=(const TimelineDataWrapper& other );
	
	~TimelineDataWrapper();

        QObjectListModel* getClips(){ return &_clips; }
        Timeline& getTimeline(){ return Projet::getInstance().getTimeline(); }
        const Timeline& getTimeline() const{ return Projet::getInstance().getTimeline(); }
        int getMaxTime() const{ return getTimeline().getMaxTime(); }
        int getTimeIn() const{ return _timeInDrag; }

	Q_INVOKABLE void play( int time );
        Q_INVOKABLE void setTimeInDrag( int timeIn )
	{
                _timeInDrag = timeIn;
                Q_EMIT timeChanged(_timeInDrag);
        }
	Q_INVOKABLE void translate( int mousePosition );
	Q_INVOKABLE void displayCursor( QString );

private:
#ifndef Q_MOC_RUN
	boost::signals::scoped_connection _dataConnection;
#endif
	int _timeInDrag;
        QObjectListModel _clips;

Q_SIGNALS:
	void clipsChanged();
	void maxTimeChanged();
	void timeChanged( int time );
	void enableUpdatesSignal( const bool update );

	public 
Q_SLOTS:
	void updateListe();
};



#endif // TIMELINEDATAWRAPPER_HPP
