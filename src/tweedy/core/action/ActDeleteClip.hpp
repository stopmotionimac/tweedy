#ifndef ACTDELETECLIP_HPP
#define	ACTDELETECLIP_HPP

#include <tweedy/core/action/IAction.hpp>

class ActDeleteClip : public IAction
{

public:
    
    ActDeleteClip();
    ~ActDeleteClip();
    
    void operator()(int currentTime);
        
};


#endif	/* ACTDELETECLIP_HPP */

