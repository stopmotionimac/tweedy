#ifndef ID_HPP
#define	ID_HPP

#include <vector>
#include <string>

class Id
{
    
public:
    
    //ctor de base
    Id(const std::string&);
    
    //ctor a partir de l'id du parent
    Id(const Id&, const std::string&);
    
    
    ~Id();
    
    
    const std::string& getIdStringForm();
    
private:
    
    std::vector<std::string> _id;
    
    
};

#endif	/* ID_HPP */

