#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QtCore/QObject>
#include <QtDeclarative/qdeclarative.h>

class Properties : public QObject
{
    Q_OBJECT
public:
    explicit Properties(QObject *parent = 0);
    Q_INVOKABLE void AfficheCurseur(QString);

};

#endif // PROPERTIES_H
