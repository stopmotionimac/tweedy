#include <tweedy/core/Application.hpp>

CommandManager& Application::getCommandManager(){
    return _cmdManager; 
}

Timeline& Application::getTimeline(){
    return _timeline;
}

void Application::printAllMedia() {
    boost::ptr_unordered_map<std::string, Imedia*>::iterator iter;
    std::cout<<"PRINT MAP APPLI"<<std::endl;
        for (iter = this->_mapMedia.begin(); iter != _mapMedia.end(); ++iter) {
            std::cout<<iter->first<<std::endl;
    }

}


//to add any media (except MediaExt)
void Application::addImedia(Imedia * media) {
    std::cout<<media->getNameMedia().string()<<std::endl;
    //ImediaType type = media->getImediaType(media);
    _mapMedia[media->getNameMedia().string()] = media;
}


void Application::makeChutier() {
    _chutier.createChutierMediaExt();
    //test import to chutier
    boost::filesystem::path url("projet/mediasExt/test.jpg");
    _chutier.importMediaToChutier(url);
}
