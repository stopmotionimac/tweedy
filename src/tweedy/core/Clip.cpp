#include <tweedy/core/Clip.hpp>

Clip& Clip::operator=(const Clip& clip){
    
    std::cout << "aaa: " << clip._id.getIdStringForm() << std::endl;
    
    _id = clip._id;
    _imgPath = clip._imgPath;
    _imgLength = clip._imgLength;
    
    _imgwidth = clip._imgwidth;
    _imgHeight = clip._imgHeight;
    
    _imgreduction = clip._imgreduction;
    
    _timeIn = clip._timeIn;
    _timeOut = clip._timeOut;
}



template<class Archive>
void Clip::serialize(Archive& ar, const unsigned int version)
{
    
    ar & _id;
    ar & _imgPath;
    ar & _timeIn;
    ar & _timeOut;
   
}