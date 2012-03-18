#ifndef IMEDIA_HPP
#define IMEDIA_HPP

#include <boost/filesystem.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

enum ImediaType {
    ImediaTypeClip,
    ImediaTypePisteClip,
    ImediaTypeMediaExt,
    ImediaTypeTimeline
};

class Imedia {
public:
    Imedia(ImediaType i):mediaType(i) {}
    //Imedia() {}
    void setNameMedia(boost::filesystem::path pathMedia) { _name = pathMedia;};
    boost::filesystem::path getNameMedia() {return _name;};
    ImediaType getImediaType(Imedia * media) { return mediaType; }

protected:
    int _idMedia;
    boost::filesystem::path _name;
    ImediaType mediaType;
    
    
private:
    /*
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {


        ar & _idMedia;
        std::string s; 
        if(Archive::is_saving::value) 
            s = _name.string(); 
        ar & boost::serialization::make_nvp("string", s); 
        if(Archive::is_loading::value)
            _name = s;
        ar & mediaType;


    }
    */
};



#endif // IMEDIA_HPP
