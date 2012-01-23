#include "ChutierMediaExt.hpp"

/*void ChutierMediaExt::makeChutier()
{

}*/

/*void ChutierMediaExt::createChutierMediaExt() {

}*/

void ChutierMediaExt::addMediaExt(MediaExt & mediaExt) {
    _mapMediaExt[mediaExt.getNameMedia().string()] = mediaExt;
}
