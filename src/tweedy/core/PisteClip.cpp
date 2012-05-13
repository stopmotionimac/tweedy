#include <tweedy/core/PisteClip.hpp>

unsigned int PisteClip::idPisteClip = 0;

PisteClip::PisteClip( const std::string& n )
        : Imedia(ImediaTypePisteClip),
        name(n)
{
    ++ idPisteClip; 
}

