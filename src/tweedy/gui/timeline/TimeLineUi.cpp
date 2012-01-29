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
    _time(0),
    _timer(new QTimer(this)),
    _isPlaying(false),
    _defautIcon( QIcon("img/none.jpg") )
 {

    _ui->setupUi(this);
    _timeline = &(Projet::getInstance().getTimeline());

    _table = new TableTimeline(this);

    _table->setIconSize(QSize(95,68));
    _table->horizontalHeader()->setDefaultSectionSize(_ui->widgetContentTable->height());
    _table->verticalHeader()->setDefaultSectionSize(100);

    //ajout de la table dans le widget
    QVBoxLayout *layout = new QVBoxLayout(_ui->widgetContentTable);
    layout->addWidget(_table);
    
    //connecter l'update de la timelineUi au signalChanged de la timeline
    TimeLineUiUpdater upd(*this);

    Projet::getInstance().getTimeline().getSignalChanged().connect(upd);
    
    createActions();
    linkButtonsWithActions();

    updateTable();
                   
    //connect(this, SIGNAL( timeChanged(int) ), this, SLOT(writeTime(int)) );
    connect( _timer, SIGNAL(timeout()), this, SLOT(increaseTime()) );
    connect( this->_table , SIGNAL( cellClicked(int,int) ), this, SLOT( getCurrentTime(int,int)));
    connect( this->_table , SIGNAL( currentCellChanged ( int , int , int , int  ) ), this, SLOT( getCurrentTime(int,int)));
        
    Q_EMIT timeChanged(_time);
        
}



void TimeLineUi::createActions(){


    _playPauseAction = new QAction(QIcon("img/icones/playS.png"),"",this);
    _playPauseAction->setShortcut(QKeySequence("Space"));
    _playPauseAction->setStatusTip("Lancer le montage");
    connect(_playPauseAction, SIGNAL(triggered()), this, SLOT(handle_playPauseAction_triggered()));

    _nextAction = new QAction(QIcon("img/icones/nextS.png"),"Suivant", this);
    _nextAction->setShortcut(QKeySequence("Alt+Right"));
    _nextAction->setStatusTip("Clip suivant");
    connect(_nextAction, SIGNAL(triggered()), this, SLOT(handle_nextAction_triggered()));

    _prevAction = new QAction(QIcon("img/icones/previousS.png"),"Precedent", this);
    _prevAction->setShortcut(QKeySequence("Alt+Left"));
    _prevAction->setStatusTip("Clip precedent");
    connect(_prevAction, SIGNAL(triggered()), this, SLOT(handle_prevAction_triggered()));
    
    _zeroAction = new QAction(QIcon("img/icones/retour0.png"),"Zero",this);
    _zeroAction->setShortcut(QKeySequence("0"));
    _zeroAction->setStatusTip("Remise a zero");
    connect(_zeroAction, SIGNAL(triggered()), this, SLOT(handle_zeroAction_triggered()));

    _plusAction = new QAction("+",this);
    //_plusAction->setShortcut(QKeySequence("Space"));
    _plusAction->setStatusTip("Augmenter la duree du clip");
    connect(_plusAction, SIGNAL(triggered()), this, SLOT(handle_plusAction_triggered()));

    _minusAction = new QAction("-", this);
    _minusAction->setStatusTip("Diminuer la duree du clip");
    connect(_minusAction, SIGNAL(triggered()), this, SLOT(handle_minusAction_triggered()));

    _blankBeforeAction = new QAction("Avant", this);
    _blankBeforeAction->setStatusTip("Frame vide avant le clip");
    connect(_blankBeforeAction, SIGNAL(triggered()), this, SLOT(handle_blankBeforeAction_triggered()));
    
    _blankAfterAction = new QAction("Apres", this);
    _blankAfterAction->setStatusTip("Frame vide après le clip");
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
    QIcon icon( QString::fromStdString("img/realTime.jpg") );
    QTableWidgetItem *newItem = new QTableWidgetItem(icon,"");
    _table->setItem(0, _timeline->maxTime(), newItem);
   
    _table->setDragEnabled(true);
    _table->verticalHeader()->setMovable(true);
    _table->setCurrentCell(0,currentTime);

   
    
}


//_______________ Write time in label and select the good cell _________________

//void TimeLineUi::writeTime(int newValue)
//{

//    _table->setCurrentCell(0,newValue);

//    if (newValue == _timeline->maxTime())
//        newValue = -1;

//   _ui->time->setNum(newValue);

//   //emitDisplayChanged();
//}


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
        _timer->start(1000);
        _isPlaying = true;
        _playPauseAction->setIcon(QIcon("img/icones/pauseS.png"));
        _playPauseAction->setStatusTip("Mettre en pause");
    }
    else
    {
        _timer->stop();
        _isPlaying = false;
        _playPauseAction->setIcon(QIcon("img/icones/playS.png"));
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
