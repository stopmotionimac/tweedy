#include <tweedy/core/Projet.hpp>

CommandManager& Projet::getCommandManager(){
    return _cmdManager; 
}

<<<<<<< HEAD
=======
Timeline& Projet::getTimeline(){
    return _timeline;
}

>>>>>>> 1e4cc5ab63b592a80a37efc74f5fe56a6e435e19
//to add any media (except MediaExt)
void Projet::addImedia(Imedia * media) {
    std::cout<<media->getNameMedia().string()<<std::endl;
    //ImediaType type = media->getImediaType(media);
    _mapMedia[media->getNameMedia().string()] = media;
}

void Projet::makeChutier() {
    _chutier.createChutierMediaExt();
    //test import to chutier
    boost::filesystem::path url("projet/mediasExt/test.jpg");
    _chutier.importMediaToChutier(url);
}

void Projet::printAllMedia() {
    boost::ptr_unordered_map<std::string, Imedia*>::iterator iter;
    std::cout<<"PRINT MAP APPLI"<<std::endl;
        for (iter = this->_mapMedia.begin(); iter != _mapMedia.end(); ++iter) {
            std::cout<<iter->first<<std::endl;
    }

<<<<<<< HEAD
}
=======
}
>>>>>>> 1e4cc5ab63b592a80a37efc74f5fe56a6e435e19
