#include <tweedy/core/Projet.hpp>


CommandManager& Projet::getCommandManager(){
    return _cmdManager; 
}


Timeline& Projet::getTimeline(){
    return _timeline;
}


Id& Projet::getId()
{
    return _id;
}


//to add any media (except MediaExt)
void Projet::addImedia(Imedia & media)
{
    using namespace boost::assign;
    ptr_map_insert( _mapMedia )( media.getNameMedia().string(), media );
}

boost::filesystem::path Projet::getNameImedia(Imedia & imedia) {
    return imedia.getNameMedia().filename();
}

ChutierMediaExt& Projet::getChutierMediaExt() {
    return _chutierMediaExt;
}

ChutierMediaExt& Projet::getChutierPictures() {
    return _chutierPictures;
}



void Projet::printAllMedia() {
    boost::ptr_unordered_map<std::string, Imedia*>::iterator iter;
    std::cout<<"PRINT MAP APPLI"<<std::endl;
    for (iter = this->_mapMedia.begin(); iter != _mapMedia.end(); ++iter)
    {
        std::cout<<iter->first<<std::endl;
    }
}


//Functions for gPhotoInstance
int Projet::tryToConnectCamera() {
    int retval = gPhotoInstance().tryToConnectCamera();
    return retval;
}

//void Projet::setFolderToSavePictures() {
//    gPhotoInstance().setFolderToSavePictures();
//}

//bool Projet::getValueCameraIsInit() {
//    return gPhotoInstance->getVarCameraIsInit();
//}

void Projet::setValueCameraIsInit(bool var) {
    gPhotoInstance().setVarCameraIsInit(var);
}

boost::filesystem::path Projet::captureToFile() {
    boost::filesystem::path fn = gPhotoInstance().captureToFile();
}
