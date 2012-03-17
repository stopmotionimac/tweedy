#include "TimelineDataWrapper.hpp"
#include <tweedy/core/action/ActDragNDropTLToTL.hpp>

#include <QtGui/QCursor>
#include <QtGui/QApplication>
#include <QtGui/QPixmap>

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeProperty>

#include <boost/signals.hpp>
#include <boost/bind.hpp>

TimelineDataWrapper::TimelineDataWrapper( QObject *parent )
: QObject( parent )
, _timeInDrag( 0 )
{
	std::cout << "TimelineDataWrapper::TimelineDataWrapper" << std::endl;
	// connecter l'update de la TimelineDataWrapper au signalChanged de la timeline
	_dataConnection = getTimeline().getSignalChanged().connect(
		boost::bind( &TimelineDataWrapper::coreDataChanged,
					this ) );

	//	updateListe();
	std::cout << "TimelineDataWrapper::TimelineDataWrapper end" << std::endl;
}

TimelineDataWrapper& TimelineDataWrapper::operator=(const TimelineDataWrapper& other )
{
	std::cout << "TimelineDataWrapper::operator=()" << std::endl;
	_timeInDrag = other._timeInDrag;
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

void TimelineDataWrapper::translate( int mousePosition )
{
	std::cout << "TimelineDataWrapper::dragNdrop" << std::endl;

	std::cout << "moooouuuuusssssseeeee " << mousePosition << std::endl;

	ActDragNDropTLToTL action;

	int timeInDrop = _timeInDrag + mousePosition;

	if( timeInDrop < 0 )
		timeInDrop = 0;
	if( timeInDrop >= getMaxTime() )
		timeInDrop = getMaxTime() - 1;

	std::string filenameDepart, filenameArrivee;
	bool foundDrag = getTimeline().findCurrentClip( filenameDepart, _timeInDrag );
	bool foundDrop = getTimeline().findCurrentClip( filenameArrivee, timeInDrop );

	if( foundDrag && foundDrop )
		action( filenameDepart, timeInDrop );

	std::cout << "TimelineDataWrapper::dragNdrop end" << std::endl;
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

/*
QDeclarativeListProperty<ClipDataWrapper> TimelineDataWrapper::getClips()
{
	return QDeclarativeListProperty<ClipDataWrapper>( this, _clips );
}

int TimelineDataWrapper::clipsCount() const
{
	return _clips.count();
}

ClipDataWrapper* TimelineDataWrapper::clips( int index ) const
{
	return _clips.at( index );
}
 */

void TimelineDataWrapper::play( int time )
{
	Q_EMIT timeChanged( time );
	/*std::cout<<time<<std::endl;
	std::string  idClip = "";
	std::string filename = "img/none.jpg";


	bool isClip = _timelineCore->findCurrentClip(idClip,time);
	if(isClip)
	{
	 filename = _timelineCore->mapClip()[idClip].imgPath().string();
	}
	_displayPixmap = new QPixmap( QString::fromStdString(filename) );*/
}
