#include <tweedy/core/Id.hpp>
#include <iostream>
#include <boost/algorithm/string/join.hpp>


//ctor de base
Id::Id(const std::string& id)
{
    //ajout de l'id dans le vector _id
    _id.push_back(id);
	///@todo boost split
}


//ctor a partir de l'id du parent
Id::Id(const Id& idParent, const std::string& id)
{
    _id = idParent._id;
    _id.push_back(id);
}

Id::~Id()
{
}

const std::string Id::getIdStringForm() const
{
    return std::string("/") + boost::algorithm::join( _id, "/" );
}

Id& Id::operator=(const Id& id)
{
    _id = id._id;
}


