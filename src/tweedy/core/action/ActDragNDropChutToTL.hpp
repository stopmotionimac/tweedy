#ifndef ACTDRAGNDROPCHUTTOTL_HPP
#define	ACTDRAGNDROPCHUTTOTL_HPP

#include <tweedy/core/action/IAction.hpp>

class ActDragNDropChutToTL : public IAction
{
    
public:

    ActDragNDropChutToTL();
    
    ~ActDragNDropChutToTL();
    
    void operator()(const std::string& idClip, int position);
};

#endif	/* ACTDRAGNDROPCHUTTOTL_HPP */
