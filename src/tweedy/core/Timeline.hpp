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
private :
        //std::vector<PisteClip> listPiste;
        typedef boost::ptr_unordered_map<std::string, Clip> UOMapClip;
        
        
        unsigned int _maxTime;
        UOMapClip _mapClip;

public :
        typedef boost::ptr_map<unsigned int, Clip*> OMapClip;
        
        Timeline(ImediaType i): Imedia(i), _maxTime(0) {}
        Timeline();
         
        //void getlistPiste ();
        //void addPiste (PisteClip & pisteClip);
        //void supprPiste (PisteClip & pisteClip);
        UOMapClip getMapClip(){ return _mapClip;}
        unsigned int maxTime(){ return _maxTime;}
        void setMaxTime();
        OMapClip getOrderedClips();
        
        void addCilp(Clip & clip, const std::string id);
        void supprClip(Clip & clip){}
        void addTimeToClip(double time, const std::string& clipName);
        

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
