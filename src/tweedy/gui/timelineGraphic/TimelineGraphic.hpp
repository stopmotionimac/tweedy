#ifndef TIMELINEGRAPHIQUE_H
#define TIMELINEGRAPHIQUE_H

#include "QmlFileWatcher.h"
#include "data/ClipDataWrapper.hpp"
#include "data/TimelineDataWrapper.hpp"
#include "data/DropArea.hpp"

#include <QtCore/QFileSystemWatcher>

#include <QtGui/QWidget>
#include <QtDeclarative/QDeclarativeView>


class TimelineGraphic : public QDeclarativeView
{
	Q_OBJECT


public:
	TimelineGraphic( QWidget * parent );
        ~TimelineGraphic();
        TimelineDataWrapper& getTimelineDataWrapper()
        {
                return _timelineData;
        }

private:
	TimelineGraphic( const TimelineGraphic& );
	TimelineGraphic& operator=( const TimelineGraphic& );
	void updateData();

        TimelineDataWrapper _timelineData;
        DropArea* _dropArea;
        QString _timelineQmlFile;
        QmlFileWatcher _qmlFileWatcher;

private Q_SLOTS:
	void onEnableUpdates( const bool update );
};

#endif
