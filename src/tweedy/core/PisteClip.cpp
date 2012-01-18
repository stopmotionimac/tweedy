#include <tweedy/core/PisteClip.hpp>


unsigned int PisteClip::idPisteClip = 0;

PisteClip::PisteClip( const std::string& n )
        : Imedia(ImediaTypePisteClip),
        name(n)
{
    ++ idPisteClip; 
}

//void PisteClip::addCilp(Clip & clip, unsigned int index)
//{
//    std::list<Clip>::iterator it;
//    it = listClip.begin();
//    for (int i=0; i<index; ++i)
//        ++ it;
//    listClip.insert(it, clip);
//
//}
