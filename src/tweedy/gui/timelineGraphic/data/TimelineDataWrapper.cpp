#include "TimelineDataWrapper.hpp"
#include <tweedy/core/action/ActDragNDropTLToTL.hpp>
#include <tweedy/core/action/ActDeleteClip.hpp>
#include <tweedy/core/Clip.hpp>

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
        // connecter l'update de la TimelineDataWrapper au signalChanged de la timeline
	_dataConnection = getTimeline().getSignalChanged().connect(
                boost::bind( &TimelineDataWrapper::coreDataChanged,this ) );

        updateListe();
}

TimelineDataWrapper& TimelineDataWrapper::operator=(const TimelineDataWrapper& other )
{
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

	_clips.clear();

	Timeline::OMapClip mapClips = getTimeline().getOrderedClips();
	int previousTimeOut = 0;

	BOOST_FOREACH( const Timeline::OMapClip::value_type& s, mapClips )
	{
		ClipDataWrapper* c = new ClipDataWrapper( *( s.second ), this );
		_clips.append( c );
	}

	Q_EMIT maxTimeChanged();

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
    //if both are aquals, do nothing
    if (timeInClipToDrag == timeToDrop)
    {
        updateListe();
        return timeInClipToDrag;
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
        _currentTime = time;
}

void TimelineDataWrapper::deleteItem(){
    //creation of ActDeleClip action
    ActDeleteClip action;

    Timeline::OMapClip mapClip = getTimeline().getOrderedClips();

    std::vector<std::string> selectedClips;

    BOOST_FOREACH( const Timeline::OMapClip::value_type& s, mapClip )
    {
        if( (*s.second)->getSelected() )
            selectedClips.push_back((*s.second)->getId().getIdStringForm());
    }

    for (int i=0; i<selectedClips.size(); ++i)
        action( getTimeline().mapClip()[ selectedClips.at(i) ]);
}

bool TimelineDataWrapper::isSelected(int timeIn)
{
    return getTimeline().getOrderedClips()[timeIn]->getSelected();
}

void TimelineDataWrapper::selectClip(int timeIn)
{
    getTimeline().selectClip(timeIn);
}

void TimelineDataWrapper::unselectAll()
{
    getTimeline().unselectAll();
}
