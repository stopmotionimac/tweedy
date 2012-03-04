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

	TimelineDataWrapper& getTimelineDataWrapper()
	{
		return _timelineData;
	}

private Q_SLOTS:
	void onQmlFileChanged( const QString &file );

private:
	TimelineDataWrapper _timelineData;

	QDeclarativeView* _qmlView;

	QString _timelineQmlFile;
	QFileSystemWatcher _qmlFileWatcher;
};

#endif
