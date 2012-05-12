#ifndef ACTDELETECLIP_HPP
#define	ACTDELETECLIP_HPP

#include <tweedy/core/action/IAction.hpp>
#include <tweedy/core/Clip.hpp>

class ActDeleteClip : public IAction
{

public:
    
    ActDeleteClip();
    ~ActDeleteClip();
    
    void operator()(Clip clip);
        
};


#endif	/* ACTDELETECLIP_HPP */

