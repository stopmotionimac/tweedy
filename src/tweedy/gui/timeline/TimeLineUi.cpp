#include "TimeLineUi.h"
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/action/ActClipSetTimeRange.hpp>
#include <tweedy/core/action/ActAddBlankBeforeClip.hpp>
#include <tweedy/core/action/ActAddBlankAfterClip.hpp>
#include <tweedy/core/action/ActDeleteClip.hpp>

#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtGui/QDragMoveEvent>


struct TimeLineUiUpdater
{
    TimeLineUiUpdater(TimeLineUi& timeline): _timelineUi(timeline)
    {

    }
    
    void operator()()
    {
        _timelineUi.updateTable();
    }
    
    TimeLineUi& _timelineUi;
};





//_________________________________ constructor ________________________________


TimeLineUi::TimeLineUi(QWidget* parent):
    QWidget(parent),
    _ui (new Ui::Timeline),
    _fps(25),
    _time(0),
    _timer(new QTimer(this)),
    _isPlaying(false),
    _defautIcon( QIcon("img/none.jpg") )
 {

    _ui->setupUi(this);
    _timeline = &(Projet::getInstance().getTimeline());

    //_ui->widgetContentTable->setContentsMargins(0,20,0,20);
    
    _table = new TableTimeline(this);

    _table->setIconSize(QSize(100,100));
    _table->horizontalHeader()->setDefaultSectionSize(100);
    _table->verticalHeader()->setDefaultSectionSize(_table->iconSize().height());

    //ajout de la table dans le widget
    QVBoxLayout *layout = new QVBoxLayout(_ui->widgetContentTable);
    layout->addWidget(_table);
    
    //connecter l'update de la timelineUi au signalChanged de la timeline
    TimeLineUiUpdater upd(*this);

    Projet::getInstance().getTimeline().getSignalChanged().connect(upd);
    
    createActions();
    linkButtonsWithActions();

    updateTable();
                   
    connect( _timer, SIGNAL(timeout()), this, SLOT(increaseTime()) );
    connect( this->_table , SIGNAL( cellClicked(int,int) ), this, SLOT( getCurrentTime(int,int)));
    connect( this->_table , SIGNAL( currentCellChanged ( int , int , int , int  ) ), this, SLOT( getCurrentTime(int,int)));
    connect(_ui->spinFps, SIGNAL(valueChanged(int)), this, SLOT(changeFps(int)) );
    
    Q_EMIT timeChanged(_time);
        
}



void TimeLineUi::createActions(){


    _playPauseAction = new QAction(QIcon("img/icones/play.png"),"",this);
    _playPauseAction->setShortcut(QKeySequence("Space"));
    _playPauseAction->setStatusTip("Play");
    connect(_playPauseAction, SIGNAL(triggered()), this, SLOT(handle_playPauseAction_triggered()));

    _nextAction = new QAction(QIcon("img/icones/next.png"),"Next", this);
    _nextAction->setShortcut(QKeySequence("Alt+Right"));
    _nextAction->setStatusTip("Next clip");
    connect(_nextAction, SIGNAL(triggered()), this, SLOT(handle_nextAction_triggered()));

    _prevAction = new QAction(QIcon("img/icones/previous.png"),"Previous", this);
    _prevAction->setShortcut(QKeySequence("Alt+Left"));
    _prevAction->setStatusTip("Previous clip");
    connect(_prevAction, SIGNAL(triggered()), this, SLOT(handle_prevAction_triggered()));
    
    _zeroAction = new QAction(QIcon("img/icones/retour0.png"),"Reset",this);
    _zeroAction->setShortcut(QKeySequence("0"));
    _zeroAction->setStatusTip("Reset");
    connect(_zeroAction, SIGNAL(triggered()), this, SLOT(handle_zeroAction_triggered()));

    _plusAction = new QAction(QIcon("img/icones/plus.png"),"+",this);
    //_plusAction->setShortcut(QKeySequence("Space"));
    _plusAction->setStatusTip("Increase duration of the clip");
    connect(_plusAction, SIGNAL(triggered()), this, SLOT(handle_plusAction_triggered()));

    _minusAction = new QAction(QIcon("img/icones/moins.png"),"-", this);
    _minusAction->setStatusTip("Decrease duration of the clip");
    connect(_minusAction, SIGNAL(triggered()), this, SLOT(handle_minusAction_triggered()));

    _blankBeforeAction = new QAction("Before", this);
    _blankBeforeAction->setStatusTip("Empty frame before the clip");
    connect(_blankBeforeAction, SIGNAL(triggered()), this, SLOT(handle_blankBeforeAction_triggered()));
    
    _blankAfterAction = new QAction("After", this);
    _blankAfterAction->setStatusTip("Empty frame after the clip");
    connect(_blankAfterAction, SIGNAL(triggered()), this, SLOT(handle_blankAfterAction_triggered()));
    
    _deleteKey = new QShortcut(this);  
    _deleteKey->setKey(QKeySequence("DEL"));  
    connect ( _deleteKey , SIGNAL( activated() ) , this , SLOT( deleteKey_activated() ) );  
    
    
}


void TimeLineUi::linkButtonsWithActions()
{
    _ui->plusButton->setDefaultAction(_plusAction);
    _ui->minusButton->setDefaultAction(_minusAction);
    _ui->blankBeforeButton->setDefaultAction(_blankBeforeAction);
    _ui->blankAfterButton->setDefaultAction(_blankAfterAction);
    
    
}


//_____________________ Update the table with list of clips ____________________


void TimeLineUi::updateTable()
{

    int currentTime = _time;
    //clear timeline
    _table->clearContents();
    while ( _table->columnCount() > 1 )
        _table->removeColumn(0);
     
    //Timeline timeline = Projet::getInstance()->getTimeline();
    //fill the whole table with blanks
    for (unsigned int i=0; i<_timeline->maxTime(); ++i)
    {
        _table->insertColumn(i);
        
        std::string header = ( boost::format("%d") %i ).str();
        _table->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(header) ) );
        
        QTableWidgetItem *newItem = new QTableWidgetItem(_defautIcon,"");
        newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);

        _table->setItem(0, i, newItem);
    }
    
    /*_table->setDragDropOverwriteMode(false);
    _table->setDragEnabled(true);
    _table->setDragDropMode(QAbstractItemView::InternalMove);*/
    
    //fill with icons
    Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
    BOOST_FOREACH( const Timeline::OMapClip::value_type& s, orderedClips )
    {
        for (unsigned int j=s.first; j<(*s.second)->timeOut(); ++j)
        {
            QIcon icon( QString::fromStdString((*s.second)->imgPath().string()) );
            QTableWidgetItem *newItem = new QTableWidgetItem(icon,"");
            newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
            _table->setItem(0, j, newItem);
        }
    }
    
    //icon for real time
    QIcon icon( QString::fromStdString("img/flux.jpg") );
    QTableWidgetItem *newItem = new QTableWidgetItem(icon,"");
    _table->setItem(0, _timeline->maxTime(), newItem);
   
    _table->setDragEnabled(true);
    _table->verticalHeader()->setMovable(true);
    _table->setCurrentCell(0,currentTime);

   
    
}


//___________ Increase current time or stop timer if last frame ________________

void TimeLineUi::increaseTime()
{
    if (_time>-1 && _time < _timeline->maxTime())
        ++ _time;
    if (_time == _timeline->maxTime())
        _time = 0; 
        
    Q_EMIT timeChanged(_time);
}



//________________ update current time when a cell is selected _________________

void TimeLineUi::getCurrentTime(int row,int column)
{
    _time = column;
    Q_EMIT timeChanged(_time);
    
}



//_______________________________ buttons slots ________________________________


void TimeLineUi::handle_playPauseAction_triggered()
{
    if (!_isPlaying)
    {
        _timer->start(1000.0 / _fps);
        _isPlaying = true;
        _playPauseAction->setIcon(QIcon("img/icones/pause.png"));
        _playPauseAction->setStatusTip("Mettre en pause");
    }
    else
    {
        _timer->stop();
        _isPlaying = false;
        _playPauseAction->setIcon(QIcon("img/icones/play.png"));
        _playPauseAction->setStatusTip("Lancer le montage");
    }
}



void TimeLineUi::handle_zeroAction_triggered()
{
   _time = 0;
   Q_EMIT timeChanged(_time);
   
}

void TimeLineUi::handle_nextAction_triggered()
{
    Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
    bool lastClip = true;
    BOOST_FOREACH( const Timeline::OMapClip::value_type& s, orderedClips )
    {
        if (s.first > _time)
        {
            lastClip = false;
            _time = s.first;
            break;
        }
        if ((*s.second)->timeOut() > _time && (*s.second)->timeOut() < _timeline->maxTime())
        {
            lastClip = false;
            _time = (*s.second)->timeOut();
            break;
        }
    }
    
    if (!lastClip)
        Q_EMIT timeChanged(_time);
        
}   

void TimeLineUi::handle_prevAction_triggered()
{
    Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
    int currentTime = _time;
    bool firstClip = true;
    BOOST_FOREACH( const Timeline::OMapClip::value_type& s, orderedClips )
    {
        if (s.first < currentTime)
        {    
            firstClip = false;
            _time = s.first;
            if ( (*s.second)->timeOut() < currentTime)
                _time = (*s.second)->timeOut();
        }
        else
            break;
    }
    
    if (!firstClip)
        Q_EMIT timeChanged(_time);
    
}


void TimeLineUi::handle_plusAction_triggered()
{ 
    
   int currentCell = _table->currentColumn();
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
       
        // création d'une action ActClipSetTimeRange
       ActClipSetTimeRange action;
       
       //declenchement de l'action
       action(_time,_ui->spinDuration->value());
   }
   
   
}


void TimeLineUi::handle_minusAction_triggered()
{ 
   int currentCell = _table->currentColumn();
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
       
        // création d'une action ActClipSetTimeRange
       ActClipSetTimeRange action;
       
       //declenchement de l'action
       action(_time,-_ui->spinDuration->value());
              
   }
}


void TimeLineUi::handle_blankBeforeAction_triggered()
{
   int currentCell = _table->currentColumn();
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
       
       // création d'une action ActAddBlankBeforeClip
       ActAddBlankBeforeClip action;
       
       //declenchement de l'action
       action(_time);
       
     
   }


}


void TimeLineUi::handle_blankAfterAction_triggered()
{
   int currentCell = _table->currentColumn();
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
      
       // création d'une action ActAddBlankAfterClip
       ActAddBlankAfterClip action;
       
       //declenchement de l'action
       action(_time);
        
   }
    
}

void TimeLineUi::deleteKey_activated()
{
  
   int currentCell = _table->currentColumn();
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
       
       //creation de l'action ActDeleteClip
       ActDeleteClip action;
       
       //declenchement de l'action
       action(_time);
       
    }

}

//_________________________________ destructor _________________________________


TimeLineUi::~TimeLineUi() 
{
}
