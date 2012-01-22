#ifndef IMEDIA_HPP
#define IMEDIA_HPP

#include <boost/filesystem.hpp>

enum ImediaType {
    ImediaTypeClip,
    ImediaTypePisteClip,
    ImediaTypeMediaExt,
    ImediaTypeTimeline
};

class Imedia {
public:
    Imedia(ImediaType i):mediaType(i) {};
    //Imedia() {};
    void setNameMedia(boost::filesystem::path pathMedia) { _name = pathMedia;};
    boost::filesystem::path getNameMedia() {return _name;};

protected:
    int _idMedia;
    boost::filesystem::path _name;
    ImediaType mediaType;
};



#endif // IMEDIA_HPP
