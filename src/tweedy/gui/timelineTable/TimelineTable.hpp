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

        //void createActions();
	void toolBar();
        //void linkButtonsWithActions();
	void updateTable();
	//void emitDisplayChanged();

public Q_SLOTS:
        //void increaseTime();
	//void writeTime(int newValue);
        //void getCurrentTime( int row, int column );
        /*void handle_plusAction_triggered();
	void handle_minusAction_triggered();
	void handle_blankBeforeAction_triggered();
	void handle_blankAfterAction_triggered();
        void deleteKey_activated();*/

Q_SIGNALS:
	void timeChanged( int newValue );
        void displayChanged( std::string filename );

private:
	Ui::TimelineTable* _ui;
	QIcon _defautIcon;

        /*QAction* _plusAction;
	QAction* _minusAction;
	QAction* _blankBeforeAction;
        QAction* _blankAfterAction;*/

	QShortcut* _deleteKey;

	Table* _table;

};

#endif
