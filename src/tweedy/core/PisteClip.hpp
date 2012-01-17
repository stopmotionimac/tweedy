#ifndef __PISTECLIP_HPP__
#define __PISTECLIP_HPP__

#include <tweedy/core/Imedia.hpp>

#include <iostream>
#include <cstdlib>
#include <list>

class PisteClip : public Imedia{
private :
    std::string name;
    static unsigned int idPisteClip;
    
public :
    PisteClip(const std::string& n );
    ~PisteClip(){}
     
};


#endif
