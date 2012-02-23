#include "ClipDataWrapper.hpp"

ClipDataWrapper::ClipDataWrapper(QObject *parent) :
    QObject(parent), _imgPath(QString::fromStdString("img/none.jpg") ), _timeIn(0), _timeOut(0)
{

}

ClipDataWrapper::ClipDataWrapper(QString imgPath, int timeIn, int timeOut, QObject *parent)
    : QObject(parent),
      _imgPath(imgPath),
      _timeIn(timeIn),
      _timeOut(timeOut)
{

}
