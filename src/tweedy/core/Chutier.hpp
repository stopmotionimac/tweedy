#ifndef CHUTIER_HPP
#define CHUTIER_HPP

#include <tweedy/core/MediaExt.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>


class Chutier
{
public:
        Chutier();
private :
        boost::ptr_unordered_map<std::string, ImediaType> mapMedia;
};

#endif // CHUTIER_HPP
