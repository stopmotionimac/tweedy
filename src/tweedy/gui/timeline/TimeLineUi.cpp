#include "TimeLineUi.h"


TimeLineUi::TimeLineUi(QDockWidget* parent): 
    QDockWidget(parent),
    _time(0),
    _timer(new QTimer(this)),
    _ui(new Ui::TimeLineUi),
    _timeline (new Timeline),
    _defautIcon( QIcon("img/none.jpg") )
 {
    _ui->setupUi(this);
    _ui->table->setIconSize(QSize(75, 75));
    
    updateTable();
    writeTime(0);
               
    connect(this, SIGNAL( timeChanged(unsigned int) ), this, SLOT(writeTime(unsigned int)) );
    connect( _timer, SIGNAL(timeout()), this, SLOT(increaseTime()) );
    connect( this->_ui->table , SIGNAL( cellClicked(int,int) ), this, SLOT( getCurrentTime(int,int)));
    
       
}


void TimeLineUi::updateTable()
{
    //fill the whole table with blanks
    for (unsigned int i=0; i<_timeline->maxTime(); ++i)
    {
        _ui->table->insertColumn(i);
        
        std::string header = ( boost::format("%d") %i ).str();
        _ui->table->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(header) ) );
        
        QTableWidgetItem *newItem = new QTableWidgetItem(_defautIcon,"");
        _ui->table->setItem(0, i, newItem);
    }
    
    //fill with icons
    Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
    BOOST_FOREACH( const Timeline::OMapClip::value_type& s, orderedClips )
    {
        for (unsigned int j=s.first; j<(*s.second)->timeOut(); ++j)
        {
            QIcon icon( QString::fromStdString((*s.second)->imgPath().string()) );
            QTableWidgetItem *newItem = new QTableWidgetItem(icon,"");
            _ui->table->setItem(0, j, newItem);
        }
    }
   
}

void TimeLineUi::emitDisplayChanged()
{
    Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
    std::string  filename = "img/none.jpg";
    BOOST_FOREACH( const Timeline::OMapClip::value_type& s, orderedClips )
    {
        if (s.first <= _time && (*s.second)->timeOut() > _time)
            filename = (*s.second)->imgPath().string();
    }
    Q_EMIT displayChanged(filename);
}


void TimeLineUi::increaseTime()
{
    if (_time < _ui->table->columnCount())
    {
        ++ _time;
        Q_EMIT timeChanged(_time);
        emitDisplayChanged(); 

    }
    else
        _timer->stop(); 

}

void TimeLineUi::writeTime(unsigned int newValue)
{
    _ui->time->setNum((int)newValue);
    _ui->table->setCurrentCell(0,(int)newValue);
    
}

void TimeLineUi::getCurrentTime(int row,int column)
{
    _time = column;
    Q_EMIT timeChanged(_time);
    emitDisplayChanged();
}



void TimeLineUi::on_playButton_clicked()
{
   _timer->start(1000);
}


void TimeLineUi::on_pauseButton_clicked()
{
   _timer->stop(); 
        
}

void TimeLineUi::on_zeroButton_clicked()
{
   _time = 0;
   Q_EMIT timeChanged(_time);
   emitDisplayChanged();
}

void TimeLineUi::on_nextButton_clicked()
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
    }
    
    if (!lastClip)
    {
        Q_EMIT timeChanged(_time);
        emitDisplayChanged();
    }
}   

void TimeLineUi::on_prevButton_clicked()
{
    /*Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
    bool firstClip = true;
    
    for (Timeline::OMapClip::iterator it=orderedClips.end(); it!=orderedClips.begin(); --it)
        if (_time >= it->first)
        {
            firstClip = false;
            --it;
            _time = it->first;
            break;
        }
               
    if (!firstClip)
    {
        Q_EMIT timeChanged(_time);
        emitDisplayChanged();
    }*/
}


void TimeLineUi::on_plusButton_clicked()
{ 
   int currentCell = _ui->table->currentColumn();
   if ( currentCell > -1 )
   {
      
       _ui->table->clearContents();
       while ( _ui->table->columnCount() > 1 )
            _ui->table->removeColumn(0);
       
       
       //actualize time in and time out of each clip following the current one
       Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
       bool isClip = false;
       std::string filename;
       BOOST_FOREACH( const Timeline::OMapClip::value_type& s, orderedClips )
       {
           if (s.first <= _time && (*s.second)->timeOut() > _time)
           {
               isClip = true;
               filename = (*s.second)->imgPath().string();
               break;
           }
       }
       
       if(isClip)
           _timeline->addTimeToClip(filename, _ui->spinDuration->value());
       
       updateTable();
       _ui->table->setCurrentCell(0,currentCell);
       
   }
   
}

void TimeLineUi::on_minusButton_clicked()
{ 
   int currentCell = _ui->table->currentColumn();
   if ( currentCell > -1 )
   {
      
       _ui->table->clearContents();
       while ( _ui->table->columnCount() > 1 )
            _ui->table->removeColumn(0);
       
       
       //actualize time in and time out of each clip following the current one
       Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
       bool isClip = false;
       std::string filename;
       BOOST_FOREACH( const Timeline::OMapClip::value_type& s, orderedClips )
       {
           if (s.first <= _time && (*s.second)->timeOut() > _time)
           {
               isClip = true;
               filename = (*s.second)->imgPath().string();
               break;
           }
       }
       
       if (isClip)
           _timeline->addTimeToClip(filename, - _ui->spinDuration->value());
       
       updateTable();
       _ui->table->setCurrentCell(0,currentCell);
       
       emitDisplayChanged();
       
   }
}


void TimeLineUi::on_blankBeforeButton_clicked()
{
   int currentCell = _ui->table->currentColumn();
   if ( currentCell > -1 )
   {
      
       _ui->table->clearContents();
       while ( _ui->table->columnCount() > 1 )
       _ui->table->removeColumn(0);
       
       //actualize time in and time out of each clip following the current one
       Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
       bool isClip = false;
       std::string filename;
       BOOST_FOREACH( const Timeline::OMapClip::value_type& s, orderedClips )
       {
           if (s.first <= _time && (*s.second)->timeOut() > _time)
           {
               isClip = true;
               filename = (*s.second)->imgPath().string();
               break;
           }
       }
       
       if (isClip)
           _timeline->addTimeToClip(filename, 1, true);
       
       updateTable();
       _ui->table->setCurrentCell(0,currentCell);
       
       emitDisplayChanged();
              
   }


}



void TimeLineUi::on_blankAfterButton_clicked()
{
   int currentCell = _ui->table->currentColumn();
   if ( currentCell > -1 )
   {
      
       _ui->table->clearContents();
       while ( _ui->table->columnCount() > 1 )
       _ui->table->removeColumn(0);
       
       //actualize time in and time out of each clip following the current one
       Timeline::OMapClip orderedClips = _timeline->getOrderedClips();
       bool isClip = false;
       std::string filename;
       BOOST_FOREACH( const Timeline::OMapClip::value_type& s, orderedClips )
       {
           if (s.first <= _time && (*s.second)->timeOut() > _time)
           {
               isClip = true;
               filename = (*s.second)->imgPath().string();
               break;
           }
       }
       
       if (isClip)
           _timeline->addTimeToClip(filename, 1, false, true);
       
       updateTable();
       _ui->table->setCurrentCell(0,currentCell);
       
              
   }
    
}





TimeLineUi::~TimeLineUi() 
{
    delete _timeline;
    delete _ui;
    delete _timer;
}
