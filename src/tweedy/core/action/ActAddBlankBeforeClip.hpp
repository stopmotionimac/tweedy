#ifndef ACTADDBLANKBEFORECLIP_HPP
#define	ACTADDBLANKBEFORECLIP_HPP

#include <tweedy/core/action/IAction.hpp>
#include <tweedy/core/Clip.hpp>

class ActAddBlankBeforeClip : public IAction
{
    
public:
    
    ActAddBlankBeforeClip();
    
    ~ActAddBlankBeforeClip();
    
    void operator()(int currentTime);
        
};

#endif	/* ACTADDBLANKBEFORECLIP_HPP */

