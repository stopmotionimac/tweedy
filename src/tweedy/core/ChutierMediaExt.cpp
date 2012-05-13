#include "ChutierMediaExt.hpp"

/*void ChutierMediaExt::createChutierMediaExt() {

}*/

boost::ptr_unordered_map<std::string, MediaExt>& ChutierMediaExt::getMapMediaExt() {
    return _mapMediaExt;
}

void ChutierMediaExt::printMapMediaExt() {
    std::cout<<"PRINT MAP MED EXT : "<<std::endl;
    std::cout<<_mapMediaExt.size()<<std::endl;
    UOMapMediaExt::iterator iter;
    for (iter = _mapMediaExt.begin(); iter != _mapMediaExt.end(); ++iter) {
        std::cout<<iter->first<<std::endl;
    }
}

void ChutierMediaExt::importMediaToChutier(boost::filesystem::path & urlMedia) {
    using namespace boost::assign;
    MediaExt mediaE(urlMedia);
    ptr_map_insert( _mapMediaExt )( mediaE.getNameMedia().string(), mediaE );

}

void ChutierMediaExt::deleteMediaFromChutier(MediaExt & media) {
    UOMapMediaExt::iterator itr = _mapMediaExt.find(media.getNameMedia().string());
    _mapMediaExt.erase(itr);
}
