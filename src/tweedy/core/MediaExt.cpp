#include "MediaExt.hpp"

BOOST_CLASS_EXPORT( MediaExt );

MediaExt* MediaExt::clone() const{
    return  new MediaExt(*this);
}
