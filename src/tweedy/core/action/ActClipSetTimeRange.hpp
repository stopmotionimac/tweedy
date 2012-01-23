#ifndef ACTCLIPSETTIMERANGE_HPP
#define	ACTCLIPSETTIMERANGE_HPP

#include <tweedy/core/action/IAction.hpp>
#include <tweedy/core/Clip.hpp>

class ActClipSetTimeRange : public IAction
{
    
public:
    
    ActClipSetTimeRange(Clip& clip, const std::string name, double value);
    
    ~ActClipSetTimeRange();
    
    
private:

    Clip& _clip;
    double _value;
        
};

#endif	/* ACTCLIPSETTIMERANGE_HPP */

