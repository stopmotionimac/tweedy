#ifndef CLIPDATAWRAPPER_HPP
#define CLIPDATAWRAPPER_HPP

#include <QtCore/QObject>

class ClipDataWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int radius READ getRadius NOTIFY radiusChanged)
public:
    explicit ClipDataWrapper(QObject *parent = 0);
    ClipDataWrapper(const ClipDataWrapper&){}
    ClipDataWrapper& operator =(const ClipDataWrapper&){}
    int getRadius();

Q_SIGNALS:
    void radiusChanged();


};

#endif // CLIPDATAWRAPPER_HPP
