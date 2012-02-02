#include <QtGui/QCursor>
#include <QtGui/QApplication>

#include "TimelineDataWrapper.hpp"
#include <tweedy/core/action/ActDragNDropTLToTL.hpp>

struct TimelineDataWrapperUpdater
{
    TimelineDataWrapperUpdater(TimelineDataWrapper& timeline): _timelineDataWrapper(timeline)
    {

    }

    void operator()()
    {
        _timelineDataWrapper.updateListe();
    }

    TimelineDataWrapper& _timelineDataWrapper;
};


TimelineDataWrapper::TimelineDataWrapper(QObject *parent) :
    QObject(parent)
{

    //connecter l'update de la TimelineDataWrapper au signalChanged de la timeline
    TimelineDataWrapperUpdater upd(*this);

    Projet::getInstance().getTimeline().getSignalChanged().connect(upd);


    _timelineCore = &(Projet::getInstance().getTimeline());
    updateListe();

}


void TimelineDataWrapper::updateListe()
{

    _clips.clear();
    Timeline::OMapClip mapClips = _timelineCore->getOrderedClips();
    BOOST_FOREACH( const Timeline::OMapClip::value_type& s, mapClips )
    {
        ClipDataWrapper* c = new ClipDataWrapper( QString::fromStdString((*s.second)->imgPath().string()), s.first, (*s.second)->timeOut(), this) ;
        _clips.append(c);
    }
    Q_EMIT clipsChanged();
}



void TimelineDataWrapper::dragNdrop(int timeInArrivee)
{
    ActDragNDropTLToTL action;

    std::string filenameDepart, filenameArrivee;
    bool found = _timelineCore->findCurrentClip(filenameDepart, _timeInDepart);
    found = _timelineCore->findCurrentClip(filenameArrivee, timeInArrivee);

    if (found && filenameDepart != filenameArrivee )
        action(filenameDepart, timeInArrivee);

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
