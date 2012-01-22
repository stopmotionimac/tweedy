#ifndef IACTION_HPP
#define	IACTION_HPP

#include <string>


class IAction {
    
public:
    
    IAction(const std::string& name);
    
    virtual ~IAction()=0;
    
    virtual std::string getName() const;

    
protected:
    
    std::string _name;
};


#endif	/* IACTION_HPP */

