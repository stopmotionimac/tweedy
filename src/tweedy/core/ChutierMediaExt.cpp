#include "ChutierMediaExt.hpp"


/*void ChutierMediaExt::createChutierMediaExt() {

}*/

/*void ChutierMediaExt::addMediaExt(MediaExt * mediaExt) {
    _mapMediaExt[mediaExt->getNameMedia().string()] = mediaExt;
}*/

void ChutierMediaExt::printMapMediaExt() {
    //std::cout<<"PRINT MAP MED EXT : "<<std::endl;
    UOMapMediaExt::iterator iter;
    for (iter = _mapMediaExt.begin(); iter != _mapMediaExt.end(); ++iter) {
        std::cout<<iter->first<<std::endl;
    }
}

void ChutierMediaExt::importMediaToChutier(boost::filesystem::path & urlMedia) {
    MediaExt * mediaE = new MediaExt(urlMedia);
    //std::cout<<"AAA"<<mediaE->getNameMedia().string()<<std::endl;
    _mapMediaExt[mediaE->getNameMedia().string()] = mediaE;
    std::cout<<"PRINT ALL MEDIA EXT"<<std::endl;
    printMapMediaExt();
    std::cout<<"/PRINT ALL MEDIA EXT"<<std::endl;
    //créer le fichier dans le dossier adhéquat
}

void ChutierMediaExt::deleteMediaFromChutier(MediaExt * media) {
   //UOMapMediaExt::iterator itr = _mapMediaExt.find( * media);
   // _mapMediaExt.erase(it);
    //UOMapClip::iterator it=_mapClip.find(clipName); _mapClip.erase(it);
}
