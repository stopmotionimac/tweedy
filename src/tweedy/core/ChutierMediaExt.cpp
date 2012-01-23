#include "ChutierMediaExt.hpp"


/*void ChutierMediaExt::createChutierMediaExt() {

}*/

void ChutierMediaExt::addMediaExt(MediaExt * mediaExt) {
    _mapMediaExt[mediaExt->getNameMedia().string()] = mediaExt;
}

void ChutierMediaExt::printMapMediaExt() {
    UOMapMediaExt::iterator iter;
    for (iter = _mapMediaExt.begin(); iter != _mapMediaExt.end(); ++iter) {
        std::cout<<iter->first<<std::endl;
    }
}
