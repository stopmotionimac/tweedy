#include <tweedy/core/Timeline.hpp>
#include <string>

#include <boost/lexical_cast.hpp>

Timeline::Timeline( const Id& idParent, const std::string& id )
: Imedia( ImediaTypeTimeline )
, _maxTime( 1 )
, _nbClip( 1 )
, _id( idParent, id )
{
	Clip realTime( "img/flux.jpg", getId(), "flux" );
        realTime.setPosition( 0, 1 );
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
        std::string clipName = findCurrentClip( currentTime );
        int timeIn = _mapClip[clipName].timeIn();

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



void Timeline::moveElement( std::string clipName, int newPosition )
{
	int difference = newPosition - _mapClip[clipName].timeIn();

	if( newPosition >= _maxTime || difference == 0 )
		return;

	int dureeClip = _mapClip[clipName].timeOut() - _mapClip[clipName].timeIn();

        std::string triggeredFilename = findCurrentClip( newPosition );

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


std::string Timeline::findCurrentClip(int time) const
{
    if (time >= _maxTime || time < 0)
        return "img/none.jpg";

    OMapClip orderedClips = getOrderedClips();

    BOOST_FOREACH( const OMapClip::value_type& s, orderedClips )
    {
        if( s.first <= time && ( *s.second )->timeOut() > time )
            return ( *s.second )->getId().getIdStringForm();
    }

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

/*void Timeline::deleteClip( const std::string& clipName )
{
	//on retire le clip de la map
	UOMapClip::iterator it = _mapClip.find( clipName );

	BOOST_ASSERT( it != _mapClip.end() );

	_mapClip.erase( it );

	//emission du signal de changement d'etat de la timeline
	_signalChanged();
}*/

void Timeline::selectClip(int timeIn)
{
    OMapClip orderedClips = getOrderedClips();

    BOOST_FOREACH( const OMapClip::value_type& s, orderedClips )
    {
        if( s.first == timeIn)
        {
            ( *s.second )->setSelected(true);
            break;
        }
    }
}



void Timeline::unselectAll()
{
    BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
    {
            s.second->setSelected(false);
    }
}



void Timeline::deleteClip(const std::string& clipName)
{
    Clip c = _mapClip[clipName];
    int duration = c.timeOut() - c.timeIn();

    UOMapClip::iterator it = _mapClip.find( clipName );
    BOOST_ASSERT( it != _mapClip.end() );
    _mapClip.erase( it );


    UOMapClip mapClips = _mapClip;
    BOOST_FOREACH( const UOMapClip::value_type& s, mapClips )
    {
        if( s.second->timeIn() > c.timeIn() )
        {
            s.second->increaseTimeIn( -duration );
            s.second->increaseTimeOut( -duration );
        }
    }

    _maxTime -= duration;
    _signalChanged();
}


/*int Timeline::getBlankDuration( Clip* clip )
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
}*/

boost::signal0<void>& Timeline::getSignalChanged()
{
	return _signalChanged;
}
