#ifndef ACTCLIPSETTIMERANGE_HPP
#define	ACTCLIPSETTIMERANGE_HPP

#include <tweedy/core/action/IAction.hpp>
#include <tweedy/core/Clip.hpp>

class ActClipSetTimeRange : public IAction
{
    
public:
    
    ActClipSetTimeRange(int currentTime, const std::string name, int value);
    
    ~ActClipSetTimeRange();
    
    
private:

    int _currentTime;
    int _value;
        
};

#endif	/* ACTCLIPSETTIMERANGE_HPP */

