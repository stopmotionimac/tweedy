#include "ClipDataWrapper.hpp"
#include <tweedy/core/Projet.hpp>

ClipDataWrapper::ClipDataWrapper(QObject *parent) :
    QObject(parent), _imgPath(QString::fromStdString("img/none.jpg") ), _timeIn(0), _timeOut(0)
{

}

ClipDataWrapper::ClipDataWrapper(Clip* clip, QObject *parent)
    : QObject(parent),
      _imgPath( QString::fromStdString(clip->imgPath().string()) ),
      _timeIn(clip->timeIn()),
      _timeOut(clip->timeOut()),
      _blankDuration( Projet::getInstance().getTimeline().getBlankDuration(clip) )
{
    std::cout << "BLANK DURATION :" << _blankDuration << std::endl;
}
