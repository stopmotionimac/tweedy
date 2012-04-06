#ifndef TIMELINEGRAPHIQUE_H
#define TIMELINEGRAPHIQUE_H

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

private:
	TimelineGraphic( const TimelineGraphic& );
	TimelineGraphic& operator=( const TimelineGraphic& );
	
public:
	TimelineDataWrapper& getTimelineDataWrapper()
	{
		return _timelineData;
	}

        void dragEnterEvent(QDragEnterEvent *event);
        void dropEvent(QDropEvent *event);
        //void setDropPosition(int pos){ _dropPos = pos;}
        void setUrlList(QList<QUrl> urlList){ _urlList = urlList; }
        //int getDropPosition(){ return _dropPos; }
        Q_INVOKABLE void insertElement( int position );

private:
	void updateData();
        QList<QUrl> _urlList;

	
private Q_SLOTS:
	void onQmlFileChanged( const QString &file );
	void onEnableUpdates( const bool update );



private:
	TimelineDataWrapper _timelineData;
        DropArea* _dropArea;
	QString _timelineQmlFile;
	QFileSystemWatcher _qmlFileWatcher;
};

#endif
