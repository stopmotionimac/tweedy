#include "ClipDataWrapper.hpp"
#include <tweedy/core/Projet.hpp>

ClipDataWrapper::ClipDataWrapper(QObject *parent) :
    QObject(parent),
    _imgPath(QString::fromStdString("img/none.jpg") ),
    _timeIn(0),
    _timeOut(0),
    _selected(false)
{

}

ClipDataWrapper::ClipDataWrapper(Clip* clip, QObject *parent)
    : QObject(parent),
      _imgPath( QString::fromStdString(clip->imgPath().string()) ),
      _timeIn(clip->timeIn()),
      _timeOut(clip->timeOut()),
      _selected(false)
{

}
