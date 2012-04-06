#ifndef DropArea_H
#define DropArea_H

#include <QtDeclarative/QDeclarativeItem>


class DropArea : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY( int dropPosition READ getDropPosition NOTIFY dropPositionChanged)

public:
    DropArea():
        _position(0)
        {}

    void setDropPosition(int pos){ _position = pos; Q_EMIT dropPositionChanged(); }
    int getDropPosition(){ return _position; }

Q_SIGNALS:
    void dropPositionChanged();

private:
    int _position;

};

#endif
