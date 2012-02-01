#ifndef ID_HPP
#define	ID_HPP

#include <vector>
#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Id
{
    
public:
    
    //ctor de base
    Id(const std::string&);
    
    //ctor a partir de l'id du parent
    Id( const Id& parent, const std::string& localId );
    
    
    ~Id();
    
    Id& operator=(const Id&);
    
    
    const std::string getIdStringForm() const;
    
private:
    
    std::vector<std::string> _id;
    
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive &, const unsigned int);
    
    
    
};

#endif	/* ID_HPP */

