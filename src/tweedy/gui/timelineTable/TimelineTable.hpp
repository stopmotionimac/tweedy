#ifndef _TIMELINE_H
#define	_TIMELINE_H

#include "ui_TimelineTable.h"

#include "Table.hpp"

#include <tweedy/core/Timeline.hpp>
#include <tweedy/core/Projet.hpp>

#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QtGui/QIcon>
#include <QtGui/QShortcut>
#include <QtGui/QLabel>

#include <QtCore/QTimer>

#include <boost/format.hpp>

#include <cstdlib>
#include <list>
#include <cstdio>

/**
 * @brief Simple frame by frame timeline.
 * 
 * Each column represents a frame.
 */
class TimelineTable : public QWidget
{
	Q_OBJECT

public:
	TimelineTable( QWidget* parent );

	~TimelineTable();

	unsigned int time()
	{
		return _time;
	}

	Ui::TimelineTable* ui()
	{
		return _ui;
	}

	Timeline& getTimeline()
	{
		return Projet::getInstance().getTimeline();
	}

	QIcon defautIcon()
	{
		return _defautIcon;
	}

	QTableWidget * getTableWidget()
	{
		return _table;
	}

	void createActions();
	void toolBar();
	void linkButtonsWithActions();

	void updateTable();
	//void emitDisplayChanged();

	QAction * getPlayPauseAction()
	{
		return _playPauseAction;
	}

	QAction * getNextAction()
	{
		return _nextAction;
	}

	QAction * getPreviousAction()
	{
		return _prevAction;
	}

	QAction * getRetour0Action()
	{
		return _zeroAction;
	}


	public 
Q_SLOTS:
	void increaseTime();
	//void writeTime(int newValue);
	void getCurrentTime( int row, int column );

	void changeFps( int value )
	{
		_fps = value;
	}


	void handle_playPauseAction_triggered();

	void handle_zeroAction_triggered();

	void handle_nextAction_triggered();
	void handle_prevAction_triggered();

	void handle_plusAction_triggered();
	void handle_minusAction_triggered();
	void handle_blankBeforeAction_triggered();
	void handle_blankAfterAction_triggered();
	void deleteKey_activated();

Q_SIGNALS:
	void timeChanged( int newValue );
	void displayChanged( std::string filename );

private:
	Ui::TimelineTable* _ui;
	int _fps;
	int _time;
	QTimer* _timer;
	bool _isPlaying;
	QIcon _defautIcon;

	QAction* _playPauseAction;
	QAction* _nextAction;
	QAction* _prevAction;
	QAction* _zeroAction;

	QAction* _plusAction;
	QAction* _minusAction;
	QAction* _blankBeforeAction;
	QAction* _blankAfterAction;

	QShortcut* _deleteKey;

	Table* _table;

};

#endif
