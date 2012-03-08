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

	Q_PROPERTY( QObjectListModel* clips READ getClips NOTIFY clipsChanged )
	Q_PROPERTY( int maxTime READ getMaxTime NOTIFY maxTimeChanged )
    Q_PROPERTY( int timeIn READ getTimeIn NOTIFY timeChanged )

public:
	explicit TimelineDataWrapper( QObject *parent = 0 );

	TimelineDataWrapper( const TimelineDataWrapper& other )
	{
		*this = other;
	}

	TimelineDataWrapper& operator=(const TimelineDataWrapper& other )
	{
		_timeInDrag = other._timeInDrag;
		_readyToDrag = other._readyToDrag;
		_clips.setObjectList( other._clips.objectList() );
		return *this;
	}
	~TimelineDataWrapper();

	QObjectListModel* getClips()
	{
		return &_clips;
	}

	Timeline& getTimeline()
	{
		return Projet::getInstance().getTimeline();
	}

	const Timeline& getTimeline() const
	{
		return Projet::getInstance().getTimeline();
	}

	int getMaxTime() const
	{
		return getTimeline().getMaxTime();
	}

        int getTimeIn() const
        {
                return _timeInDrag;
        }

	Q_INVOKABLE void play( int time );

        Q_INVOKABLE void setTimeInDrag( int timeIn )
	{
                _timeInDrag = timeIn;
		_readyToDrag = true;
                Q_EMIT timeChanged(_timeInDrag);
        }
	Q_INVOKABLE void translate( int mousePosition );

	Q_INVOKABLE void displayCursor( QString );

private:
#ifndef Q_MOC_RUN
	boost::signals::scoped_connection _dataConnection;
#endif
	int _timeInDrag;
	bool _readyToDrag;
	QObjectListModel _clips;

Q_SIGNALS:
	void clipsChanged();
	void maxTimeChanged();
	void timeChanged( int time );

	public 
Q_SLOTS:
	void updateListe();
};



#endif // TIMELINEDATAWRAPPER_HPP
