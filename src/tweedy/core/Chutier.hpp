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
        void addMediaExt(MediaExt & mediaExt);

private :
        boost::ptr_unordered_map<std::string, MediaExt> _mapMediaExt;
};

void ChutierMediaExt::addMediaExt(MediaExt & mediaExt) {
    _mapMediaExt[mediaExt.getNameMedia().string()] = mediaExt;
}

#endif // CHUTIER_HPP
