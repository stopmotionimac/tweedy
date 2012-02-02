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

class ChutierMediaExt
{
public:
    ChutierMediaExt() {}
        boost::ptr_unordered_map<std::string, MediaExt>& getMapMediaExt();
        //call if we import a media
        void importMediaToChutier(boost::filesystem::path & urlMedia);
        void deleteMediaFromChutier(MediaExt & media);
        //n'arrive pas à le mettre dans le .cpp sans erreur...
        void createChutierMediaExt() {
//                boost::filesystem::path path("projet/mediasExt");
//                //std::cout<<"FOLDER : "<<path.string()<<std::endl;
//
//                if(!boost::filesystem::exists(path))
//                {
//                    std::cout << "no such folder" << std::endl;
//                    return;
//                }
//
//                if(boost::filesystem::is_directory(path))
//                {
//                    for(boost::filesystem::directory_iterator it(path), end; it != end; ++it)
//                    {
//                        //If there is a folder
//                        if(boost::filesystem::is_directory(it->status()))
//                        {
//                            std::cout << it->path().filename() << "[DIR]" << std::endl;
//                        }
//                        //if there is a file
//                        else if(boost::filesystem::is_regular_file(it->status()))
//                        {
//                            MediaExt * mediaE = new MediaExt(it->path().filename());
//                            //add to chutier
//                            _mapMediaExt[mediaE->getNameMedia().string()] = mediaE;
//                            //std::cout << it->path().filename() << std::endl;
//                        }
//                    }
//                }
//                //printMapMediaExt();
        }

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
