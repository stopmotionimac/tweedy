#ifndef TIMELINEGRAPHIQUE_H
#define TIMELINEGRAPHIQUE_H

#include "data/ClipDataWrapper.hpp"
#include "data/TimelineDataWrapper.hpp"

#include <QtCore/QFileSystemWatcher>

#include <QtGui/QWidget>
#include <QtDeclarative/QDeclarativeView>

class TimelineGraphic : public QDeclarativeView
{
	Q_OBJECT
public:
	TimelineGraphic( QWidget * parent );

private:
	TimelineGraphic( const TimelineGraphic& );
	TimelineGraphic& operator=( const TimelineGraphic& );
	
public:
	TimelineDataWrapper& getTimelineDataWrapper()
	{
		return _timelineData;
	}
		
private:
	void updateData();
	
private Q_SLOTS:
	void onQmlFileChanged( const QString &file );
	void onEnableUpdates( const bool update );

private:
	TimelineDataWrapper _timelineData;

	QString _timelineQmlFile;
	QFileSystemWatcher _qmlFileWatcher;
};

#endif
