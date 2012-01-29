#ifndef ACTADDBLANKBEFORECLIP_HPP
#define	ACTADDBLANKBEFORECLIP_HPP

#include <tweedy/core/action/IAction.hpp>
#include <tweedy/core/Clip.hpp>

class ActAddBlankBeforeClip : public IAction
{
    
public:
    
    ActAddBlankBeforeClip(int currentTime, const std::string name);
    
    ~ActAddBlankBeforeClip();
    
    
private:

    int _currentTime;
    int _value;
        
};

#endif	/* ACTADDBLANKBEFORECLIP_HPP */

