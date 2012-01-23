#ifndef __TIMELINE_HPP__
#define __TIMELINE_HPP__

//#include <tweedy/core/PisteClip.hpp>
#include <tweedy/core/Clip.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/foreach.hpp>

class Timeline : public Imedia{

public :

        typedef boost::ptr_unordered_map<std::string, Clip> UOMapClip;
        typedef boost::ptr_map<unsigned int, Clip*> OMapClip;
        
        Timeline();
         
        //void getlistPiste ();
        //void addPiste (PisteClip & pisteClip);
        //void supprPiste (PisteClip & pisteClip);
        UOMapClip mapClip(){ return _mapClip;}
        unsigned int maxTime(){ return _maxTime;}
        void setMaxTime();
        OMapClip getOrderedClips();
        
        void addCilp(Clip & clip);
        void deleteClip(const std::string& clipName){ UOMapClip::iterator it=_mapClip.find(clipName); _mapClip.erase(it); }
        void deleteBlank(int time);
        void addTimeToClip(const std::string& clipName, double time, bool blankBefore=false, bool blankAfter=false);
        bool findCurrentClip(std::string & filename, int time);

        
private :
        unsigned int _maxTime;
        UOMapClip _mapClip;
        

};

/*void Timeline::addCilp(Clip & clip, const std::string id)
{
//    std::list<Clip>::iterator it;
//    it = listClip.begin();
//    for (int i=0; i<index; ++i)
//        ++ it;
//    listClip.insert(it, clip);
}*/

#endif
