#ifndef IMEDIA_HPP
#define IMEDIA_HPP

#include<string>

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

protected:
    int IdMedia;
    std::string name;

    ImediaType mediaType;
};



#endif // IMEDIA_HPP
