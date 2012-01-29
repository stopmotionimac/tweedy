#ifndef ACTDELETECLIP_HPP
#define	ACTDELETECLIP_HPP

#include <tweedy/core/action/IAction.hpp>

class ActDeleteClip : public IAction
{

public:
    
    ActDeleteClip(int currentTime, const std::string name);
    ~ActDeleteClip();
    
private:

    int _currentTime;
        
};


#endif	/* ACTDELETECLIP_HPP */

