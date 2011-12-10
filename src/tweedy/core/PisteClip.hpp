#ifndef __PISTECLIP_HPP__
#define __PISTECLIP_HPP__

#include "Clip.hpp"

#include <iostream>
#include <cstdlib>
#include <vector>

class PisteClip {
private :
        std::vector<Clip> listClip;
        unsigned int idPisteClip;
        std::string name;
public :
        void getlistClip();
        void addCilp(Clip & clip);
        void supprClip(Clip & clip);
};


#endif
