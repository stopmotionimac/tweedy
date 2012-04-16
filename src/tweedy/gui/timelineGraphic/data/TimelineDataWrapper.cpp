#include "TimelineDataWrapper.hpp"
#include <tweedy/core/action/ActDragNDropTLToTL.hpp>
#include <tweedy/core/action/ActDeleteClip.hpp>


#include <QtGui/QCursor>
#include <QtGui/QApplication>
#include <QtGui/QPixmap>

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeProperty>

#include <boost/signals.hpp>
#include <boost/bind.hpp>

TimelineDataWrapper::TimelineDataWrapper( QObject *parent )
: QObject( parent ),
  _timeMarker(0)
{
	std::cout << "TimelineDataWrapper::TimelineDataWrapper" << std::endl;
	// connecter l'update de la TimelineDataWrapper au signalChanged de la timeline
	_dataConnection = getTimeline().getSignalChanged().connect(
                boost::bind( &TimelineDataWrapper::coreDataChanged,this ) );


        updateListe();
	std::cout << "TimelineDataWrapper::TimelineDataWrapper end" << std::endl;
}

TimelineDataWrapper& TimelineDataWrapper::operator=(const TimelineDataWrapper& other )
{
	std::cout << "TimelineDataWrapper::operator=()" << std::endl;
        _clips.setObjectList( other._clips.objectList() );
	return *this;
}

TimelineDataWrapper::~TimelineDataWrapper()
{
}

void TimelineDataWrapper::coreDataChanged()
{
	updateListe();
}

void TimelineDataWrapper::updateListe()
{
	// Prevent all connected widgets to not update content view at each
	// modification step (which creates flick artefacts).
	// Update/repaint widgets connected to this view at the end of all modifications.
	Q_EMIT enableUpdatesSignal( false );

	static int i = 0;
	++i;
	std::cout << "TimelineDataWrapper ptr: " << this << std::endl;
	std::cout << "TimelineDataWrapper::updateListe: " << i << std::endl;

	_clips.clear();

	Timeline::OMapClip mapClips = getTimeline().getOrderedClips();
	int previousTimeOut = 0;

	BOOST_FOREACH( const Timeline::OMapClip::value_type& s, mapClips )
	{
		ClipDataWrapper* c = new ClipDataWrapper( *( s.second ), this );
		_clips.append( c );
	}

	Q_EMIT maxTimeChanged();
	std::cout << "TimelineDataWrapper::updateListe end" << std::endl;

	Q_EMIT enableUpdatesSignal( true );

}

int TimelineDataWrapper::getMarkerPosition( int timeToDrop, bool positiveMove )
{
   timeToDrop = std::max(timeToDrop,0);
   timeToDrop = std::min(timeToDrop,getMaxTime() - 1);

   std::string filename = getTimeline().findCurrentClip(timeToDrop);

   if (positiveMove)
        return getTimeline().mapClip()[filename].timeOut();
   else
        return getTimeline().mapClip()[filename].timeIn();
}


int TimelineDataWrapper::translate( int timeInClipToDrag, int timeToDrop )
{
    // si les 2 sont égaux on ne fait rien

    if (timeInClipToDrag == timeToDrop)
    {
        std::cout << "ekljnjknelk" <<std::endl;
        updateListe();
        return -1;
    }
    else
    {
        ActDragNDropTLToTL action;

        timeToDrop = std::max(timeToDrop,0);
        timeToDrop = std::min(timeToDrop,getMaxTime() - 1);

        std::string filenameDepart = getTimeline().findCurrentClip(timeInClipToDrag );
        std::string filenameArrivee = getTimeline().findCurrentClip(timeToDrop );

        int returnedValue = getTimeline().mapClip()[filenameArrivee].timeIn();
        action( filenameDepart, timeToDrop );

        return returnedValue;

    }
}


void TimelineDataWrapper::displayCursor( QString typeCurseur )
{
	QCursor curseur;
	if( typeCurseur.toUpper() == "HAND" )
		curseur = QCursor( Qt::PointingHandCursor );
	else if( typeCurseur.toUpper() == "SCALE" )
		curseur = QCursor( Qt::SizeHorCursor );
	else
		curseur = QCursor( Qt::ArrowCursor );
	QApplication::setOverrideCursor( curseur );
}

void TimelineDataWrapper::displayCurrentClip( int time )
{
	Q_EMIT timeChanged( time );
}


void TimelineDataWrapper::deleteItem( int time ){

    //creation de l'action ActDeleteClip
    ActDeleteClip action;
    //declenchement de l'action
    action(time);

}


void TimelineDataWrapper::changeSelected( int time )
{
    for (int i=0; i<_clips.size(); ++i )
    {
        ClipDataWrapper * c = dynamic_cast< ClipDataWrapper *>(_clips[i]);
        if (c->getTimeIn() == time)
            c->setSelected(true);
        else
            c->setSelected(false);
    }

}
