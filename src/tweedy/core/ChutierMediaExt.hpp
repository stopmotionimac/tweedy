#ifndef CHUTIERMEDIAEXT_HPP
#define CHUTIERMEDIAEXT_HPP

#include <iostream>
#include <tweedy/core/MediaExt.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>
#include <boost/filesystem.hpp>


class ChutierMediaExt
{
public:
        ChutierMediaExt();
        //void makeChutier();
        //call if we import a media
        void updateChutierMediaExt() {}
        //n'arrive pas à le mettre dans le .cpp sans erreur...
        void createChutierMediaExt(){
                boost::filesystem::path path("projet/mediasExt");
                std::cout<<"FOLDER : "<<path.string()<<std::endl;

                if(!boost::filesystem::exists(path))
                {
                    std::cout << "no such folder" << std::endl;
                    return;
                }

                if(boost::filesystem::is_directory(path))
                {
                    for(boost::filesystem::directory_iterator it(path), end; it != end; ++it)
                    {
                        //If there is a folder
                        if(boost::filesystem::is_directory(it->status()))
                        {
                            std::cout << it->path().filename() << "[DIR]" << std::endl;
                            //insert
                            //"projet/medias/Ext" + "/" + it->path().filename()
                        }
                        //if there is a file
                        else if(boost::filesystem::is_regular_file(it->status()))
                        {
                            std::cout << it->path().filename() << std::endl;
                        }
                    }
                }
        }
        void addMediaExt(MediaExt & mediaExt);

private :
        boost::ptr_unordered_map<std::string, MediaExt> _mapMediaExt;
};



#endif // CHUTIER_HPP
