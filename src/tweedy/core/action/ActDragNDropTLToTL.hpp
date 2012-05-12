#ifndef ACTDRAGNDROPTLTOTL_HPP
#define	ACTDRAGNDROPTLTOTL_HPP

#include <tweedy/core/action/IAction.hpp>

class ActDragNDropTLToTL : public IAction
{
    
public:

    ActDragNDropTLToTL();
    
    ~ActDragNDropTLToTL();
    
    void operator()(const std::string& idClip, int position);
};

#endif	/* ACTDRAGNDROPTLTOTL_HPP */
