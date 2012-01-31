#ifndef TIMELINEGRAPHIQUE_H
#define TIMELINEGRAPHIQUE_H

#include <QtGui/QWidget>
#include <QtDeclarative/QDeclarativeView>

#include "properties.h"

class TimelineGraphique : public QWidget
{
public:
    TimelineGraphique(QWidget * parent);

    void update();

private:
    Properties _prop;

    QDeclarativeView* _qmlView;
};

#endif // TIMELINEGRAPHIQUE_H
