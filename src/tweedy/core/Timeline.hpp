#ifndef __TIMELINE_HPP__
#define __TIMELINE_HPP__

//#include <tweedy/core/PisteClip.hpp>
#include <tweedy/core/Clip.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <boost/ptr_container/ptr_unordered_map.hpp>

class Timeline : public Imedia{
private :
        //std::vector<PisteClip> listPiste;
        boost::ptr_unordered_map<std::string, Clip> mapClip;

public :
        //void getlistPiste ();
        //void addPiste (PisteClip & pisteClip);
        //void supprPiste (PisteClip & pisteClip);
        boost::ptr_unordered_map<std::string, Clip> getMapClip(){ return mapClip;}
        void addCilp(Clip & clip, const std::string id);
        void supprClip(Clip & clip){  }

};

void Timeline::addCilp(Clip & clip, const std::string id)
{
//    std::list<Clip>::iterator it;
//    it = listClip.begin();
//    for (int i=0; i<index; ++i)
//        ++ it;
//    listClip.insert(it, clip);
}

#endif
