#include <tweedy/core/Id.hpp>
#include <iostream>
#include <boost/algorithm/string/join.hpp>



//ctor de base
Id::Id(const std::string& id)
{
    
    //ajout de l'id dans le vector _id
    _id.push_back(id);
}


//ctor a partir de l'id du parent
Id::Id(const Id& idParent, const std::string& id)
{

    for(int i = 0 ; i < idParent._id.size() ; ++i)
    {
        _id.push_back(idParent._id[i]);
    }
    
    _id.push_back(id);
    
}

Id::~Id()
{
    
}

const std::string Id::getIdStringForm() const
{
    return std::string("/") + boost::algorithm::join( _id, "/" );
    /*
    //nouvelle string vide
    std::string id ="";
    
    //on concatene dans une string tous les id du vector _id
    for(int i = 0 ; i < _id.size()-1 ; ++i)
    {
        
        id += _id[i] + "/" ;

    }
    
    id += _id[_id.size()-1];
    
    return id;*/
    
}

Id& Id::operator=(const Id& id){
    
    _id = id._id;
}
