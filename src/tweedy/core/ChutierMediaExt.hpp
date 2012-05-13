#ifndef CHUTIERMEDIAEXT_HPP
#define CHUTIERMEDIAEXT_HPP

#include <iostream>
#include <tweedy/core/MediaExt.hpp>
#include <boost/assign/ptr_map_inserter.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/ptr_container/serialize_ptr_unordered_map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>

class ChutierMediaExt
{
public:
    ChutierMediaExt() {}
        boost::ptr_unordered_map<std::string, MediaExt>& getMapMediaExt();
        //call if we import a media
        void importMediaToChutier(boost::filesystem::path & urlMedia);
        void deleteMediaFromChutier(MediaExt & media);
        void printMapMediaExt ();
        
private :
        typedef boost::ptr_unordered_map<std::string, MediaExt> UOMapMediaExt;
        UOMapMediaExt _mapMediaExt;
        
        friend class boost::serialization::access;
    
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar & _mapMediaExt;
        } 
};

#endif // CHUTIER_HPP
