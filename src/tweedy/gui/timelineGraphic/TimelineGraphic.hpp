#ifndef TIMELINEGRAPHIQUE_H
#define TIMELINEGRAPHIQUE_H

#include "data/ClipDataWrapper.hpp"
#include "data/TimelineDataWrapper.hpp"

#include <QtCore/QFileSystemWatcher>

#include <QtGui/QWidget>
#include <QtDeclarative/QDeclarativeView>

class TimelineGraphic : public QWidget
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
#ifndef Q_MOC_RUN
	boost::signals::scoped_connection _dataConnection;
#endif
	TimelineDataWrapper _timelineData;

	QDeclarativeView* _qmlView;

	QString _timelineQmlFile;
	QFileSystemWatcher _qmlFileWatcher;
};

#endif
