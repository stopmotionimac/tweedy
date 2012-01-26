#include <tweedy/core/Timeline.hpp>

Timeline::Timeline(): Imedia(ImediaTypeTimeline), _maxTime(0)
{
    Clip c1("img/tweedy0.jpg" );
    c1.setPosition(0,1);
    Clip c2( "img/tweedy1.jpg" );
    c2.setPosition(1,2);
    Clip c3( "img/tweedy2.jpg" );
    c3.setPosition(2,3);
    Clip c4( "img/tweedy3.jpg" );
    c4.setPosition(3,4);
    Clip c5("img/tweedy4.jpg" );
    c5.setPosition(4,5);
    Clip c6( "img/tweedy5.jpg" );
    c6.setPosition(5,6);
    Clip c7( "img/tweedy6.jpg" );
    c7.setPosition(6,7);
        
    _mapClip[c1.imgPath().string()] = c1 ;
    _mapClip[c2.imgPath().string()] = c2 ;
    _mapClip[c3.imgPath().string()] = c3 ;
    _mapClip[c4.imgPath().string()] = c4 ;
    _mapClip[c5.imgPath().string()] = c5 ;
    _mapClip[c6.imgPath().string()] = c6 ;
    _mapClip[c7.imgPath().string()] = c7 ;
    
    
    setMaxTime();
}

Timeline::Timeline(const Timeline& timeline) : Imedia(timeline)
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



void Timeline::addClip(Clip & clip) {
    _mapClip[clip.imgPath().string()] = clip;
}


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
    
    
    
    Clip c(newClipName);
    c.setPosition(timeIn, timeIn+1);
    _mapClip[newClipName] = c;
        
    
    setMaxTime();
    
    _signalChanged();
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

    //décale les clips suivants
    BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
    {
      if (s.second->timeIn() > _mapClip[clipName].timeIn())
      {
          s.second->setTimeIn(time);
          s.second->setTimeOut(time);
      }      
    }
    
    _signalChanged();
    
                
}


//__________________ Find corresponding clip of current time ___________________


bool Timeline::findCurrentClip(std::string & filename, int time)
{
    OMapClip orderedClips = getOrderedClips();
    BOOST_FOREACH( const OMapClip::value_type& s, orderedClips )
    {
        if (s.first <= time && (*s.second)->timeOut() > time)
        {
            filename = (*s.second)->imgPath().string();
            return true;
        }
    }
    return false;
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

void Timeline::deleteBlank(int time)
{
    OMapClip orderedClips = getOrderedClips();
    BOOST_FOREACH( const OMapClip::value_type& s, orderedClips )
    {
        if (s.first > time)
        {
            (*s.second)->setTimeIn(-1);
            (*s.second)->setTimeOut(-1);
        }
    }
    --_maxTime;
    _signalChanged();
}


boost::signal0<void>& Timeline::getSignalChanged(){
     return _signalChanged;
 }
