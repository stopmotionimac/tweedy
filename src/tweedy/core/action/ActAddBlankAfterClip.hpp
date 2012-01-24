#ifndef ACTADDBLANKAFTERCLIP_HPP
#define	ACTADDBLANKAFTERCLIP_HPP

#include <tweedy/core/action/IAction.hpp>
#include <tweedy/core/Clip.hpp>

class ActAddBlankAfterClip : public IAction
{
    
public:
    
    ActAddBlankAfterClip(int currentTime, const std::string name, int value);
    
    ~ActAddBlankAfterClip();
    
    
private:

    int _currentTime;
    int _value;
        
};

#endif	/* ACTADDBLANKAFTERCLIP_HPP */

