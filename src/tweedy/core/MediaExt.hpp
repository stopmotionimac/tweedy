#ifndef MEDIAEXT_HPP
#define MEDIAEXT_HPP

#include <boost/filesystem/path.hpp>
#include <tweedy/core/Imedia.hpp>

class MediaExt : public Imedia {
public:
    MediaExt();
    MediaExt(const boost::filesystem::path & url) : Imedia(ImediaTypeMediaExt){ this->_name = url;};
    
    
};

#endif // MEDIAEXT_HPP
