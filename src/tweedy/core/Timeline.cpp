#include <tweedy/core/Timeline.hpp>



Timeline::Timeline(): Imedia(ImediaTypeTimeline), _maxTime(0)
{
    Clip c1("img/tweedy0.jpg" );
    c1.setPosition(0,3);
    Clip c2( "img/tweedy1.jpg" );
    c2.setPosition(5,7);
    Clip c3( "img/tweedy2.jpg" );
    c3.setPosition(7,10);
    Clip c4( "img/tweedy3.jpg" );
    c4.setPosition(11,12);
    
    _mapClip[c1.imgPath().string()] = c1 ;
    _mapClip[c2.imgPath().string()] = c2 ;
    _mapClip[c3.imgPath().string()] = c3 ;
    _mapClip[c4.imgPath().string()] = c4 ;
    
    
    setMaxTime();
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


void Timeline::addTimeToClip(const std::string& clipName, double time, bool blankBefore, bool blankAfter)
{
    if (time < 0)
    {
      double dureeClip = _mapClip[clipName].timeOut() - _mapClip[clipName].timeIn();
      if (-time >= dureeClip)
          time = -dureeClip + 1;
    }

    _maxTime += time;

    if(!blankAfter)
    {
        if (blankBefore)
            _mapClip[clipName].setTimeIn(time);
        _mapClip[clipName].setTimeOut(time);
    }

    BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
    {
      if (s.second->timeIn() > _mapClip[clipName].timeIn())
      {
          s.second->setTimeIn(time);
          s.second->setTimeOut(time);
      }      
    }
    
    
    
        
}

void Timeline::setMaxTime()
{
    unsigned int max = 0;
    BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
    {
       if ( s.second->timeOut() > max)
           max = s.second->timeOut();
    }
    _maxTime = max;

}
