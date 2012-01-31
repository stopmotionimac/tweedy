#include "ClipDataWrapper.hpp"

ClipDataWrapper::ClipDataWrapper(QObject *parent) :
    QObject(parent)
{

}

int ClipDataWrapper::getRadius()
{
    return 50;
}
