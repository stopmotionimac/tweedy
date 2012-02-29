#include "TimelineDataWrapper.hpp"
#include <tweedy/core/action/ActDragNDropTLToTL.hpp>

#include <QtGui/QCursor>
#include <QtGui/QApplication>
#include <QtGui/QPixmap>

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeProperty>

#include <boost/signals.hpp>
#include <boost/bind.hpp>

TimelineDataWrapper::TimelineDataWrapper(QObject *parent)
    : QObject(parent)
    , _timeInDrag(0)
    , _readyToDrag(false)
{
    std::cout << "TimelineDataWrapper::TimelineDataWrapper" << std::endl;
    // connecter l'update de la TimelineDataWrapper au signalChanged de la timeline
    _dataConnection = getTimeline().getSignalChanged().connect(
                boost::bind( &TimelineDataWrapper::updateListe,
                             *this ) );

    updateListe();
    std::cout << "TimelineDataWrapper::TimelineDataWrapper end" << std::endl;
}

TimelineDataWrapper::~TimelineDataWrapper()
{
}

void TimelineDataWrapper::updateListe()
{
    std::cout << "TimelineDataWrapper::updateListe" << std::endl;

    _clips.clear();
	
    Timeline::OMapClip mapClips = getTimeline().getOrderedClips();
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

    if ( previousTimeOut < getTimeline().maxTime() )
    {
        ClipDataWrapper* c = new ClipDataWrapper( QString::fromStdString("img/none.jpg"), previousTimeOut, getTimeline().maxTime(), this) ;
        _clips.append(c);
    }

    std::cout << "TimelineDataWrapper::updateListe _clips.size(): " << _clips.size() << std::endl;
    Q_EMIT clipsChanged();

//    Q_EMIT fullUpdate();
    std::cout << "TimelineDataWrapper::updateListe end" << std::endl;
}



void TimelineDataWrapper::dragNdrop(int mousePosition)
{
    std::cout << "TimelineDataWrapper::dragNdrop" << std::endl;
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
    bool foundDrag = getTimeline().findCurrentClip(filenameDepart, _timeInDrag);
    bool foundDrop = getTimeline().findCurrentClip(filenameArrivee, mousePosition/100);

    if (foundDrag && foundDrop)
        getTimeline().moveElement(filenameDepart, mousePosition/100);
        //action(filenameDepart, mousePosition/100);

    _readyToDrag = false;

    std::cout << "TimelineDataWrapper::dragNdrop end" << std::endl;
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

/*
QDeclarativeListProperty<ClipDataWrapper> TimelineDataWrapper::getClips( )
{
	return QDeclarativeListProperty<ClipDataWrapper>( this, _clips );
}

int TimelineDataWrapper::clipsCount( ) const
{
	return _clips.count();
}

ClipDataWrapper* TimelineDataWrapper::clips( int index ) const
{
	return _clips.at( index );
}
*/

void TimelineDataWrapper::play(int time)
{
    Q_EMIT timeChanged(time);
    /*std::cout<<time<<std::endl;
    std::string  idClip = "";
    std::string filename = "img/none.jpg";


    bool isClip = _timelineCore->findCurrentClip(idClip,time);
    if(isClip)
    {
     filename = _timelineCore->mapClip()[idClip].imgPath().string();
    }
    _displayPixmap = new QPixmap( QString::fromStdString(filename) );*/
}
