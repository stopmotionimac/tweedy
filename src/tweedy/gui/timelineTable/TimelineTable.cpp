#include "TimelineTable.hpp"

#include <tweedy/core/Projet.hpp>
#include <tweedy/core/action/ActClipSetTimeRange.hpp>
#include <tweedy/core/action/ActDeleteClip.hpp>

#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtGui/QDragMoveEvent>

struct TimeLineUiUpdater
{
	TimeLineUiUpdater( TimelineTable & timeline )
	: _timelineUi( timeline )
	{}
	void operator()()
	{
		_timelineUi.updateTable();
	}

	TimelineTable& _timelineUi;
};

TimelineTable::TimelineTable( QWidget* parent )
: QWidget( parent )
, _ui( new Ui::TimelineTable )
, _defautIcon( QIcon( "img/none.jpg" ) )
{
	_ui->setupUi( this );

	_table = new Table( this );

	_table->setIconSize( QSize( 100, 100 ) );
	_table->horizontalHeader()->setDefaultSectionSize( 100 );
	_table->verticalHeader()->setDefaultSectionSize( _table->iconSize().height() );

        //add the table on the widget
	QVBoxLayout *layout = new QVBoxLayout( _ui->widgetContentTable );
	layout->addWidget( _table );

        //connect timelineUi updater to the timeline signalChanged
	TimeLineUiUpdater upd( *this );

	getTimeline().getSignalChanged().connect( upd );

	updateTable();

	connect( this->_table, SIGNAL( cellClicked( int, int ) ), this, SLOT( getCurrentTime( int, int ) ) );
	connect( this->_table, SIGNAL( currentCellChanged( int, int, int, int ) ), this, SLOT( getCurrentTime( int, int ) ) );
	connect( _ui->spinFps, SIGNAL( valueChanged( int ) ), this, SLOT( changeFps( int ) ) );

}

TimelineTable::~TimelineTable()
{

}
