#include <tweedy/core/Id.hpp>
#include <iostream>
#include <boost/algorithm/string/join.hpp>

//basic ctor
Id::Id(const std::string& id)
{
    //add id in the vector
    _id.push_back(id);
}

//ctor based on parent's id
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
