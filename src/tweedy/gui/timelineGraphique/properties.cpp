#include <QtGui/QCursor>
#include <QtGui/QApplication>
#include <QtGui/QColor>

#include <iostream>

#include "properties.h"



Properties::Properties(QObject *parent) :
    QObject(parent)
{

}

void Properties::afficheCurseur(QString typeCurseur)
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

void Properties::afficheXClip(qreal x)
{
    std::cout<<x<<std::endl;
}

void Properties::update()
{
    std::cout<<"Update QML Timeline"<<std::endl;
}

int Properties::getClipRadius()
{
    return 50;
}

TimelineDataWrapper Properties::getTimelineData()
{
    return _timelineDataWrapper;
}

