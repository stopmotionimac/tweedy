#ifndef __TIMELINE_HPP__
#define __TIMELINE_HPP__

#include "PisteClip.hpp"

#include <iostream>
#include <cstdlib>
#include <vector>

class Timeline : public Imedia{
private :
        std::vector<PisteClip> listPiste;

public :
        void getlistPiste ();
        void addPiste (PisteClip & pisteClip);
        void supprPiste (PisteClip & pisteClip);

};


#endif
