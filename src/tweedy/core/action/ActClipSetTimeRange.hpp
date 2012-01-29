#ifndef ACTCLIPSETTIMERANGE_HPP
#define	ACTCLIPSETTIMERANGE_HPP

#include <tweedy/core/action/IAction.hpp>
#include <tweedy/core/Clip.hpp>

class ActClipSetTimeRange : public IAction
{
    
public:
    
    ActClipSetTimeRange();
    
    ~ActClipSetTimeRange();
    
    void operator()(int currentTime, int value);
    
};

#endif	/* ACTCLIPSETTIMERANGE_HPP */

