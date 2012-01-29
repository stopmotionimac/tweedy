#include <tweedy/core/Clip.hpp>


Clip::Clip(const Clip& clip): Imedia(ImediaTypeClip)
{
    _imgPath = clip._imgPath;
    _imgLength = clip._imgLength;
    
    _imgwidth = clip._imgwidth;
    _imgHeight = clip._imgHeight;
    
    _imgreduction = clip._imgreduction;
    
    _timeIn = clip._timeIn;
    _timeOut = clip._timeOut;
}

Clip& Clip::operator=(const Clip& clip){
    
    _imgPath = clip._imgPath;
    _imgLength = clip._imgLength;
    
    _imgwidth = clip._imgwidth;
    _imgHeight = clip._imgHeight;
    
    _imgreduction = clip._imgreduction;
    
    _timeIn = clip._timeIn;
    _timeOut = clip._timeOut;
}



