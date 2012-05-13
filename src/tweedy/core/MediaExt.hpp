#ifndef MEDIAEXT_HPP
#define MEDIAEXT_HPP

#include <boost/noncopyable.hpp>
#include <boost/filesystem/path.hpp>
#include <tweedy/core/Imedia.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

class MediaExt : public Imedia {
public:
    MediaExt()  : Imedia(ImediaTypeMediaExt) {}

    MediaExt(const boost::filesystem::path & url) : Imedia(ImediaTypeMediaExt) {
        this->_name = url;
    }

    MediaExt* clone() const;

private:

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        // serialize base class information
        ar & boost::serialization::base_object<Imedia>(*this);
    }
};

#endif // MEDIAEXT_HPP
