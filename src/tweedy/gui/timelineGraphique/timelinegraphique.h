#ifndef TIMELINEGRAPHIQUE_H
#define TIMELINEGRAPHIQUE_H

#include "ClipDataWrapper.hpp"
#include "TimelineDataWrapper.hpp"

#include <QtCore/QFileSystemWatcher>

#include <QtGui/QWidget>
#include <QtDeclarative/QDeclarativeView>


class TimelineGraphique : public QWidget
{
    Q_OBJECT
public:
    TimelineGraphique(QWidget * parent);

    TimelineDataWrapper* getTimelineDataWrapper() { return &_timelineData; }

public Q_SLOTS:
    void updateTweedyDatas();
	void onQmlFileChanged( const QString &file );

private:
    TimelineDataWrapper _timelineData;
	
    QDeclarativeView* _qmlView;

	QString _timelineQmlFile;
	QFileSystemWatcher _qmlFileWatcher;
};

#endif // TIMELINEGRAPHIQUE_H
