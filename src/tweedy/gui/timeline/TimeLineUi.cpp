#include "TimeLineUi.h"


//_________________________________ constructor ________________________________


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
               
    connect(this, SIGNAL( timeChanged(int) ), this, SLOT(writeTime(int)) );
    connect( _timer, SIGNAL(timeout()), this, SLOT(increaseTime()) );
    connect( this->_ui->table , SIGNAL( cellClicked(int,int) ), this, SLOT( getCurrentTime(int,int)));
    
       
}


//_____________________ Update the table with list of clips ____________________


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
    
    //icon for real time
    QIcon icon( QString::fromStdString("img/realTime.jpg") );
    QTableWidgetItem *newItem = new QTableWidgetItem(icon,"");
    _ui->table->setItem(0, _timeline->maxTime(), newItem);
   
}






//____________________ Let the view display the good picture ___________________


void TimeLineUi::emitDisplayChanged()
{
    std::string  filename = "img/none.jpg";
    
    if (_time == _timeline->maxTime())
        //afficher le temps reel
        filename = "img/realTime.jpg";
    else
        bool isClip = _timeline->findCurrentClip(filename,_time);
    
    Q_EMIT displayChanged(filename);
}


//___________ Increase current time or stop timer if last frame ________________

void TimeLineUi::increaseTime()
{
    if (_time < _timeline->maxTime() - 1)
        ++ _time;
    else
       _time = 0; 
        
    Q_EMIT timeChanged(_time);
    emitDisplayChanged(); 
        

}


//_______________ Write time in label and select the good cell _________________

void TimeLineUi::writeTime(int newValue)
{
    _ui->table->setCurrentCell(0,newValue);
    
    if (newValue == _timeline->maxTime())
        newValue = -1;
    
    _ui->time->setNum(newValue);   
}


//________________ update current time when a cell is selected _________________

void TimeLineUi::getCurrentTime(int row,int column)
{
    _time = column;
       
    Q_EMIT timeChanged(_time);
    emitDisplayChanged();
}



//_______________________________ buttons slots ________________________________


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
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
      
       _ui->table->clearContents();
       while ( _ui->table->columnCount() > 1 )
            _ui->table->removeColumn(0);
       
       
       std::string filename;
       bool isClip = _timeline->findCurrentClip(filename,_time);
       
       if(isClip)
           _timeline->addTimeToClip(filename, _ui->spinDuration->value());
       
       updateTable();
       _ui->table->setCurrentCell(0,currentCell);
       
   }
   
}


void TimeLineUi::on_minusButton_clicked()
{ 
   int currentCell = _ui->table->currentColumn();
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
      
       _ui->table->clearContents();
       while ( _ui->table->columnCount() > 1 )
            _ui->table->removeColumn(0);
       
       
       std::string filename;
       bool isClip = _timeline->findCurrentClip(filename,_time);
       
       
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
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
      
       _ui->table->clearContents();
       while ( _ui->table->columnCount() > 1 )
       _ui->table->removeColumn(0);
       
       std::string filename;
       bool isClip = _timeline->findCurrentClip(filename,_time);
       
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
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
      
       _ui->table->clearContents();
       while ( _ui->table->columnCount() > 1 )
       _ui->table->removeColumn(0);
       
       std::string filename;
       bool isClip = _timeline->findCurrentClip(filename,_time);
       
       if (isClip)
           _timeline->addTimeToClip(filename, 1, false, true);
       
       updateTable();
       _ui->table->setCurrentCell(0,currentCell);
       
              
   }
    
}

void TimeLineUi::on_deleteButton_clicked()
{
   int currentCell = _ui->table->currentColumn();
   if ( currentCell > -1 && currentCell < _timeline->maxTime() )
   {
       _ui->table->clearContents();
       while ( _ui->table->columnCount() > 1 )
       _ui->table->removeColumn(0);
       
       std::string filename;
       bool isClip = _timeline->findCurrentClip(filename,_time);
       
       if (isClip)
           _timeline->deleteClip(filename);
       else
           _timeline->deleteBlank(_time);
              
       updateTable();
       _ui->table->setCurrentCell(0,currentCell);
       
       emitDisplayChanged();
   }

}

//_________________________________ destructor _________________________________


TimeLineUi::~TimeLineUi() 
{
    delete _timeline;
    delete _ui;
    delete _timer;
}
