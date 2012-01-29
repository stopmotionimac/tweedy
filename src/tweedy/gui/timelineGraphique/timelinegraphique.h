#ifndef TIMELINEGRAPHIQUE_H
#define TIMELINEGRAPHIQUE_H

#include <QtGui/QWidget>
#include <QtDeclarative/QDeclarativeView>

#include "properties.h"

class TimelineGraphique : public QWidget
{
public:
    TimelineGraphique(QWidget * parent);

private:
    Properties _prop;
};

#endif // TIMELINEGRAPHIQUE_H
