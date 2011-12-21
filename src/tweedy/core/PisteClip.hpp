#ifndef __PISTECLIP_HPP__
#define __PISTECLIP_HPP__

#include "Clip.hpp"

#include <iostream>
#include <cstdlib>
#include <list>

class PisteClip : public Imedia{
private :
    std::string name;
    std::list<Clip> listClip;
    static unsigned int idPisteClip;
    
public :
    PisteClip(std::string n);
    ~PisteClip(){}
    std::list<Clip> getlistClip(){ return listClip;}
    void addCilp(Clip & clip, unsigned int index);
    //void supprClip(Clip & clip){ listClip.remove(clip); }
     
};


#endif
