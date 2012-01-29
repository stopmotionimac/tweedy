#ifndef __TIMELINE_HPP__
#define __TIMELINE_HPP__

#include <tweedy/core/Clip.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/foreach.hpp>
#include <boost/signal.hpp>

class Timeline : public Imedia{

public :

        typedef boost::ptr_unordered_map<std::string, Clip> UOMapClip;
        typedef boost::ptr_map<unsigned int, Clip*> OMapClip;
        
        Timeline();
        Timeline(const Timeline&);
         
        //void getlistPiste ();
        //void addPiste (PisteClip & pisteClip);
        //void supprPiste (PisteClip & pisteClip);
        UOMapClip mapClip(){ return _mapClip;}
        unsigned int maxTime(){ return _maxTime;}
        void setMaxTime();
        OMapClip getOrderedClips();
        
        void moveElement(std::string filename, int newPosition);
        void addClip(Clip & clip);
        void deleteClip(const std::string& clipName);
        void deleteBlank(int time);
        void insertClip(const std::string& newClipName, double currentTime);
        void addTimeToClip(const std::string& clipName, double time, bool blankBefore=false, bool blankAfter=false);
        bool findCurrentClip(std::string & filename, int time);

        boost::signal0<void>& getSignalChanged();
        
private :
    
        unsigned int _maxTime;
        UOMapClip _mapClip;
        
        boost::signal0<void> _signalChanged;

};

#endif
