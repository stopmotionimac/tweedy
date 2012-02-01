#ifndef __TIMELINE_HPP__
#define __TIMELINE_HPP__

#include <tweedy/core/Clip.hpp>
#include <tweedy/core/Id.hpp>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/foreach.hpp>
#include <boost/signal.hpp>
#include <boost/ptr_container/serialize_ptr_unordered_map.hpp>

class Timeline : public Imedia{

public :

        typedef boost::ptr_unordered_map<std::string, Clip> UOMapClip;
        typedef boost::ptr_map<unsigned int, Clip*> OMapClip;
        
        Timeline(const Id& idParent, const std::string& id);
        Timeline(const Timeline&);
         
        //void getlistPiste ();
        //void addPiste (PisteClip & pisteClip);
        //void supprPiste (PisteClip & pisteClip);
        UOMapClip& mapClip(){ return _mapClip;}
        unsigned int& maxTime(){ return _maxTime;}
        void setMaxTime();
        OMapClip getOrderedClips();
        
        void moveElement(std::string filename, int newPosition);
        void addClip(Clip & clip);
        void deleteClip(const std::string& clipName);
        
        void addBlank(const std::string& clipName, bool blankBefore = false);
        void deleteBlank(int time);
        
        void insertClip(Clip , double currentTime);
        //void insertClip(const std::string& newClipName, double currentTime);
        void addTimeToClip(const std::string& clipName, double decalage);
        bool findCurrentClip(std::string & filename, int time);
        
        
        Id& getId();
        unsigned int& getNbClip();
        
        boost::signal0<void>& getSignalChanged();
        
private :
    
        unsigned int _nbClip;
        unsigned int _maxTime;
        UOMapClip _mapClip;
        
        boost::signal0<void> _signalChanged;
        
        Id _id;
        
        friend class boost::serialization::access;
    
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version)
        {


            ar & _nbClip;
            ar & _maxTime;
            ar & _mapClip;
            ar & _id;


        }

};

#endif
