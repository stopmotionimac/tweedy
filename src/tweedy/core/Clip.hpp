#ifndef __CLIP_HPP__
#define __CLIP_HPP__

#include "Imedia.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

class Clip : public Imedia {
public:
    Clip(char* url)
        : _imgPath(url),
        _imgLength(0.0), 
        _imgwidth(0), 
        _imgHeight(0), 
        _imgreduction(0), 
        _timeIn(0), 
        _timeOut(0){}
        
    ~Clip(){}
    
    char* imgPath(){ return _imgPath; }
    unsigned int timeIn(){ return _timeIn; }
    unsigned int timeOut(){ return _timeOut; }
    void setPosition(unsigned int ti, unsigned int to){ _timeIn = ti; _timeOut = to; }
    
protected :
    char* _imgPath;
    float _imgLength;
    unsigned int _imgwidth;
    unsigned int _imgHeight;
    unsigned int _imgreduction;
    unsigned int _timeIn;
    unsigned int _timeOut;
};

#endif
