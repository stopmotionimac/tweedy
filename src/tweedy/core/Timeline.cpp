#include <tweedy/core/Timeline.hpp>
#include <string>

#include <boost/lexical_cast.hpp>

Timeline::Timeline( const Id& idParent, const std::string& id )
: Imedia( ImediaTypeTimeline ),
  _maxTime( 2 ),
  _nbClip( 1 ),
  _id( idParent, id )
{
	Clip realTime( "img/flux.jpg", getId(), "flux" );
	realTime.setPosition( 1, 2 );
	_mapClip[realTime.getId().getIdStringForm()] = realTime;
}


Timeline::Timeline( const Timeline& timeline )
: Imedia( timeline )
, _id( timeline._id )
{
	_maxTime = timeline._maxTime;
	_mapClip = timeline._mapClip;
}

Timeline::OMapClip Timeline::getOrderedClips()
{
	OMapClip orderedClips;

	BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
	{
		orderedClips[s.second->timeIn()] = s.second;
	}
	return orderedClips;
}

const Timeline::OMapClip Timeline::getOrderedClips() const
{
	return const_cast<Timeline&> ( *this ).getOrderedClips();
}

const Id& Timeline::getId() const
{
	return _id;
}

void Timeline::addClip( const Clip& clip )
{
	_mapClip[clip.getId().getIdStringForm()] = clip;
	updateMaxTime();
	_signalChanged();
}

void Timeline::insertClip( Clip& newClip, double currentTime )
{
	std::string clipName;
	bool found = findCurrentClip( clipName, currentTime );
	int timeIn = currentTime;

	if( found )
		timeIn = _mapClip[clipName].timeIn();

	//décale les clips suivants

	BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
	{
		if( s.second->timeIn() >= timeIn )
		{
			s.second->increaseTimeIn( 1 );
			s.second->increaseTimeOut( 1 );
		}
	}

	newClip.setPosition( timeIn, timeIn + 1 );
	_mapClip[newClip.getId().getIdStringForm()] = newClip;


	updateMaxTime();

	_signalChanged();
}

/*
void Timeline::insertClip(const std::string& newClipName, double currentTime)
{
		std::string currentFilename;
		bool found = findCurrentClip(currentFilename, currentTime);
		int timeIn = currentTime;

		if (found)
				timeIn = _mapClip[currentFilename].timeIn();

		//décale les clips suivants
		BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
		{
		  if (s.second->timeIn() >= timeIn)
		  {
				  s.second->setTimeIn(1);
				  s.second->setTimeOut(1);
		  }
		}


		Clip c(newClipName,this->getId(),"clip" + boost::lexical_cast<std::string>(_nbClip++));
		c.setPosition(timeIn, timeIn+1);
		_mapClip[newClipName] = c;


		setMaxTime();

		_signalChanged();
}
 */


void Timeline::moveElement( std::string clipName, int newPosition )
{
	int difference = newPosition - _mapClip[clipName].timeIn();

	if( newPosition >= _maxTime || difference == 0 )
		return;

	int dureeClip = _mapClip[clipName].timeOut() - _mapClip[clipName].timeIn();

	std::string triggeredFilename;
	bool found = findCurrentClip( triggeredFilename, newPosition );

	if( !found )
		return;

	int addedValueCurrent;

	if( difference > 0 )
	{
		addedValueCurrent = _mapClip[triggeredFilename].timeOut() - dureeClip;

		BOOST_FOREACH( const Timeline::UOMapClip::value_type& s, _mapClip )
		{
			if( s.second->timeIn() > _mapClip[clipName].timeIn() && s.second->timeIn() <= newPosition )
			{
				s.second->increaseTimeIn( -dureeClip );
				s.second->increaseTimeOut( -dureeClip );
			}
		}
	}
	else
	{
		addedValueCurrent = _mapClip[triggeredFilename].timeIn();

		BOOST_FOREACH( const Timeline::UOMapClip::value_type& s, _mapClip )
		{
			if( s.second->timeIn() >= addedValueCurrent && s.second->timeIn() < _mapClip[clipName].timeIn() )
			{
				s.second->increaseTimeIn( dureeClip );
				s.second->increaseTimeOut( dureeClip );
			}
		}

	}


	_mapClip[clipName].setPosition( addedValueCurrent, addedValueCurrent + dureeClip );

	_signalChanged();

}

void Timeline::addBlank( const std::string& clipName, bool blankBefore )
{
	if( blankBefore )
	{

		BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
		{
			if( s.second->timeIn() >= _mapClip[clipName].timeIn() )
			{
				s.second->increaseTimeIn( 1 );
				s.second->increaseTimeOut( 1 );
			}
		}
	}

	else
		BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
	{
		if( s.second->timeIn() > _mapClip[clipName].timeIn() )
		{
			s.second->increaseTimeIn( 1 );
			s.second->increaseTimeOut( 1 );
		}
	}


	_maxTime++;

	_signalChanged();

}

void Timeline::addTimeToClip( const std::string& clipName, double decalage )
{
	if( decalage < 0 )
	{
		double dureeClip = _mapClip[clipName].timeOut() - _mapClip[clipName].timeIn();
		if( -decalage >= dureeClip )
			decalage = -dureeClip + 1;
	}

	_mapClip[clipName].increaseTimeOut( decalage );

	BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
	{
		if( s.second->timeIn() > _mapClip[clipName].timeIn() )
		{
			s.second->increaseTimeIn( decalage );
			s.second->increaseTimeOut( decalage );
		}
	}

	_maxTime += decalage;

	_signalChanged();

}


//__________________ Find corresponding clip of current time ___________________

bool Timeline::findCurrentClip( std::string & idClip, int time ) const
{
	OMapClip orderedClips = getOrderedClips();

	BOOST_FOREACH( const OMapClip::value_type& s, orderedClips )
	{
		if( s.first <= time && ( *s.second )->timeOut() > time )
		{
			idClip = ( *s.second )->getId().getIdStringForm();
			return true;
		}
	}
	return false;
}

void Timeline::updateMaxTime()
{
	unsigned int max = 0;

	BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
	{
		if( s.second->timeOut() > max )
			max = s.second->timeOut();
	}
	_maxTime = max;

}

void Timeline::deleteClip( const std::string& clipName )
{
	//on retire le clip de la map
	UOMapClip::iterator it = _mapClip.find( clipName );

	BOOST_ASSERT( it != _mapClip.end() );

	_mapClip.erase( it );

	//emission du signal de changement d'etat de la timeline
	_signalChanged();
}

void Timeline::deleteBlank( int time )
{
    std::string filename;
    int i = time - 1;

    while (!findCurrentClip(filename,i) && i>0)
    {
        --i;
    }

	OMapClip orderedClips = getOrderedClips();

	BOOST_FOREACH( const OMapClip::value_type& s, orderedClips )
	{
		if( s.first > time )
		{
                        ( *s.second )->increaseTimeIn( i - time );
                        ( *s.second )->increaseTimeOut( i - time );
		}
	}
        _maxTime += i-time;
	_signalChanged();
}

/*nouvelle fonctions de suppression
void Timeline::deleteBlank(Clip* clip)
{
		int blankDuration = getBlankDuration(clip);
		UOMapClip mapClips = _mapClip;

		BOOST_FOREACH( const UOMapClip::value_type& s, mapClips )
		{
			if( s.second->timeIn() >= clip->timeIn() )
				{
						s.second->increaseTimeIn( -blankDuration );
						s.second->increaseTimeOut( -blankDuration );
				}
		}

		updateMaxTime();
		_signalChanged();
}

void Timeline::deleteClip(Clip* clip)
{
		int duration = clip->timeOut() - clip->timeIn();
		UOMapClip mapClips = _mapClip;

		BOOST_FOREACH( const UOMapClip::value_type& s, mapClips )
		{
			if( s.second->timeIn() > clip->timeIn() )
				{
						s.second->increaseTimeIn( -duration );
						s.second->increaseTimeOut( -duration );
				}
		}

		_mapClip.erase(clip->imgPath().string());
		updateMaxTime();
		_signalChanged();
}

 */

int Timeline::getBlankDuration( Clip* clip )
{
	OMapClip orderedClips = getOrderedClips();
	int previousTimeOut = 0;

	BOOST_FOREACH( const OMapClip::value_type& s, orderedClips )
	{
		if( clip->timeIn() >= ( *s.second )->timeOut() )
		{
			previousTimeOut = ( *s.second )->timeOut();
		}
		else
			break;
	}
	return clip->timeIn() - previousTimeOut;
}

boost::signal0<void>& Timeline::getSignalChanged()
{
	return _signalChanged;
}
