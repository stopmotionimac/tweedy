#ifndef ID_HPP
#define	ID_HPP

#include <vector>
#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class Id
{
    
public:
    
    //basic ctor
    Id(const std::string&);
    
    //ctor based on parent's id
    Id( const Id& parent, const std::string& localId );
    
    ~Id();
    
    Id& operator=(const Id&);
    
    const std::string getIdStringForm() const;
    
private:
    std::vector<std::string> _id;
    
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & _id;
    }
};

#endif	/* ID_HPP */
