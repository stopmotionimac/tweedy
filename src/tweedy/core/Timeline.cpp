#include <tweedy/core/Timeline.hpp>
#include <string>

#include <boost/lexical_cast.hpp>


Timeline::Timeline(const Id& idParent, const std::string& id)
: Imedia(ImediaTypeTimeline), _maxTime(0), _nbClip(0),_id(idParent,id)
{
  
    
    Clip c1("img/tweedy0.jpg", getId() , "clip" + boost::lexical_cast<std::string>(_nbClip++) );
    c1.setPosition(0,1);
    
    Clip c2( "img/tweedy1.jpg", getId() , "clip" + boost::lexical_cast<std::string>(_nbClip++) );
    c2.setPosition(1,2);
    
    Clip c3( "img/tweedy2.jpg", getId() , "clip" + boost::lexical_cast<std::string>(_nbClip++) );
    c3.setPosition(2,3);

    Clip c4( "img/tweedy3.jpg", getId() , "clip" + boost::lexical_cast<std::string>(_nbClip++) );
    c4.setPosition(3,4);
    
    Clip c5("img/tweedy4.jpg", getId() , "clip" + boost::lexical_cast<std::string>(_nbClip++) );
    c5.setPosition(4,5);
    
    Clip c6( "img/tweedy5.jpg", getId() , "clip" + boost::lexical_cast<std::string>(_nbClip++) );
    c6.setPosition(5,6);
    
    Clip c7( "img/tweedy6.jpg", getId() , "clip" + boost::lexical_cast<std::string>(_nbClip++) );
    c7.setPosition(6,7);
 

    _mapClip[c1.getId().getIdStringForm()] = c1 ;
    _mapClip[c2.getId().getIdStringForm()] = c2 ;
    _mapClip[c3.getId().getIdStringForm()] = c3 ;
    _mapClip[c4.getId().getIdStringForm()] = c4 ;
    _mapClip[c5.getId().getIdStringForm()] = c5 ;
    _mapClip[c6.getId().getIdStringForm()] = c6 ;
    _mapClip[c7.getId().getIdStringForm()] = c7 ;
  
    
    setMaxTime();
}

Timeline::Timeline(const Timeline& timeline) : Imedia(timeline),_id(timeline._id)
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



Id& Timeline::getId()
{
    return _id;
}



void Timeline::addClip(Clip& clip) {
    _mapClip[clip.getId().getIdStringForm()] = clip;
     setMaxTime();
    _signalChanged();
}




void Timeline::insertClip(Clip newClip, double currentTime)
{
    std::string clipName;
    bool found = findCurrentClip(clipName, currentTime);
    int timeIn = currentTime;
    
    if (found)
        timeIn = _mapClip[clipName].timeIn();
    
    //décale les clips suivants
    BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
    {
      if (s.second->timeIn() >= timeIn)
      {
          s.second->setTimeIn(1);
          s.second->setTimeOut(1);
      }      
    }
        
    newClip.setPosition(timeIn, timeIn+1);
    _mapClip[newClip.getId().getIdStringForm()] = newClip;
        
    
    setMaxTime();
    
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


void Timeline::moveElement(std::string clipName, int newPosition)
{
    if (newPosition == _maxTime)
        return;
    
    int move = newPosition - _mapClip[clipName].timeIn();
    
    int duree = _mapClip[clipName].timeOut() - _mapClip[clipName].timeIn();
    if (move > 0)
        duree *= -1;
    
    if (move > 0)
        BOOST_FOREACH( const Timeline::UOMapClip::value_type& s, _mapClip)
        {
            if (s.second->timeIn() > _mapClip[clipName].timeIn() && s.second->timeIn() <= newPosition)
            {
                s.second->setTimeIn(duree);
                s.second->setTimeOut(duree);
            }
        }
        
    else
        BOOST_FOREACH( const Timeline::UOMapClip::value_type& s, _mapClip)
        {
            if (s.second->timeIn() >= newPosition && s.second->timeIn() < _mapClip[clipName].timeIn())
            {
                s.second->setTimeIn(duree);
                s.second->setTimeOut(duree);
            }
        }
    
     
    _mapClip[clipName].setTimeIn(move);
    _mapClip[clipName].setTimeOut(move);
    
    _signalChanged();
   
}



void Timeline::addBlank(const std::string& clipName, bool blankBefore)
{
    if (blankBefore)
    {
        BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
        {
          if (s.second->timeIn() >= _mapClip[clipName].timeIn())
          {
              s.second->setTimeIn(1);
              s.second->setTimeOut(1);
          }      
        }
    }
    
    else 
        BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
        {
          if (s.second->timeIn() > _mapClip[clipName].timeIn())
          {
              s.second->setTimeIn(1);
              s.second->setTimeOut(1);
          }      
        }
     
        
    _maxTime++;
    
    _signalChanged();

}



void Timeline::addTimeToClip(const std::string& clipName, double decalage)
{
    if (decalage < 0)
    {
      double dureeClip = _mapClip[clipName].timeOut() - _mapClip[clipName].timeIn();
      if (-decalage >= dureeClip)
          decalage = -dureeClip + 1;
    }

    _mapClip[clipName].setTimeOut(decalage);
    
    BOOST_FOREACH( const UOMapClip::value_type& s, _mapClip )
        {
          if (s.second->timeIn() > _mapClip[clipName].timeIn())
          {
              s.second->setTimeIn(decalage);
              s.second->setTimeOut(decalage);
          }      
        }
        
    _maxTime += decalage;
    
    _signalChanged();
                
}


//__________________ Find corresponding clip of current time ___________________


bool Timeline::findCurrentClip(std::string & idClip, int time)
{
    OMapClip orderedClips = getOrderedClips();
    BOOST_FOREACH( const OMapClip::value_type& s, orderedClips )
    {
        if (s.first <= time && (*s.second)->timeOut() > time)
        {
            idClip = (*s.second)->getId().getIdStringForm();
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

void Timeline::deleteClip(const std::string& clipName)
{
    std::cout << clipName << std::endl;
    //on retire le clip de la map
    UOMapClip::iterator it=_mapClip.find(clipName);
    
    BOOST_ASSERT( it != _mapClip.end() );
    
    _mapClip.erase(it);
    
    //emission du signal de changement d'etat de la timeline
    _signalChanged();
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



unsigned int& Timeline::getNbClip()
{
    return _nbClip;
}


boost::signal0<void>& Timeline::getSignalChanged(){
     return _signalChanged;
 }
