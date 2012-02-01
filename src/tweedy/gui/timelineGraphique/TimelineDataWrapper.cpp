#include <QtGui/QCursor>
#include <QtGui/QApplication>

#include "TimelineDataWrapper.hpp"

TimelineDataWrapper::TimelineDataWrapper(QObject *parent) :
    QObject(parent)
{
    _timelineCore = &(Projet::getInstance().getTimeline());
    Timeline::OMapClip mapClips = _timelineCore->getOrderedClips();


    BOOST_FOREACH( const Timeline::OMapClip::value_type& s, mapClips )
    {
        ClipDataWrapper* c = new ClipDataWrapper( QString::fromStdString((*s.second)->imgPath().string()), s.first, (*s.second)->timeOut(), this) ;
        _clips.append(c);
    }


}




void TimelineDataWrapper::dragNdrop(int timeInArrivee)
{
    std::cout << "dragndrop" << std::endl;

    std::string filenameDepart, filenameArrivee;
    bool found = _timelineCore->findCurrentClip(filenameDepart, _timeInDepart);
    found = _timelineCore->findCurrentClip(filenameArrivee, timeInArrivee);

    if (found && filenameDepart != filenameArrivee )
        _timelineCore->moveElement(filenameDepart, timeInArrivee);
}

void TimelineDataWrapper::displayCursor(QString typeCurseur)
{
    QCursor curseur;
    if(typeCurseur.toUpper() == "HAND")
        curseur = QCursor(Qt::PointingHandCursor);
    else if(typeCurseur.toUpper() == "SCALE")
        curseur = QCursor(Qt::SizeHorCursor);
    else
        curseur = QCursor(Qt::ArrowCursor);
    QApplication::setOverrideCursor(curseur);
}


QList<QObject*> TimelineDataWrapper::getClips()
{
    return _clips;
}

//int TimelineDataWrapper::getSizeClips()
//{
//    return _clips.size();
//}
