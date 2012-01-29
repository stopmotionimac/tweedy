#ifndef ACTADDBLANKAFTERCLIP_HPP
#define	ACTADDBLANKAFTERCLIP_HPP

#include <tweedy/core/action/IAction.hpp>
#include <tweedy/core/Clip.hpp>

class ActAddBlankAfterClip : public IAction
{
    
public:
    
    ActAddBlankAfterClip();
    
    ~ActAddBlankAfterClip();
    
    void operator()(int currentTime);
    
        
};

#endif	/* ACTADDBLANKAFTERCLIP_HPP */

