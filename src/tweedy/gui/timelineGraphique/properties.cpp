#include <QtGui/QCursor>
#include <QtGui/QApplication>

#include "properties.h"

Properties::Properties(QObject *parent) :
    QObject(parent)
{
}

void Properties::AfficheCurseur(QString typeCurseur)
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
