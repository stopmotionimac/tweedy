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
    QObject(parent), _timeInDrag(0), _readyToDrag(false)
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
    int previousTimeOut = 0;
    BOOST_FOREACH( const Timeline::OMapClip::value_type& s, mapClips )
    {

        if ( s.first - previousTimeOut > 0 )
        {
            ClipDataWrapper* blank = new ClipDataWrapper( QString::fromStdString("img/none.jpg"), previousTimeOut, s.first, this) ;
            _clips.append(blank);
        }

        ClipDataWrapper* c = new ClipDataWrapper( QString::fromStdString((*s.second)->imgPath().string()), s.first, (*s.second)->timeOut(), this) ;
        _clips.append(c);

        previousTimeOut = (*s.second)->timeOut();
    }

    if ( previousTimeOut < _timelineCore->maxTime() )
    {
        ClipDataWrapper* c = new ClipDataWrapper( QString::fromStdString("img/none.jpg"), previousTimeOut, _timelineCore->maxTime(), this) ;
        _clips.append(c);
    }

    Q_EMIT clipsChanged();

}



void TimelineDataWrapper::dragNdrop(int mousePosition)
{
    //std::cout << index << std::endl;

    //if (!_readyToDrag)
       // return;

    ActDragNDropTLToTL action;

    if (_timeInDrag == mousePosition/100)
    {
        updateListe();
        return;
    }

    std::string filenameDepart, filenameArrivee;
    bool foundDrag = _timelineCore->findCurrentClip(filenameDepart, _timeInDrag);
    bool foundDrop = _timelineCore->findCurrentClip(filenameArrivee, mousePosition/100);

    if (foundDrag && foundDrop)
        _timelineCore->moveElement(filenameDepart, mousePosition/100);
        //action(filenameDepart, mousePosition/100);

    _readyToDrag = false;

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
