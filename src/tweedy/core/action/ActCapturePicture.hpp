#ifndef ACTCAPTUREPICTURE_HPP
#define	ACTCAPTUREPICTURE_HPP

#include <tweedy/core/action/IAction.hpp>

class ActCapturePicture : public IAction
{

public:
    
    ActCapturePicture();
    ~ActCapturePicture();
    
    void operator()(const std::string);
};
#endif	/* ACTCAPTUREPICTURE_HPP */

