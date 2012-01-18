/*
 * File:   TimeLine.cpp
 * Author: julien
 *
 * Created on 19 décembre 2011, 17:51
 */


#include "TimeLine.h"


TimeLine::TimeLine(QDockWidget* parent): 
    QDockWidget(parent),
    _time(0),
    _timer(new QTimer(this)),
    _ui(new Ui::TimeLine),
    _defautIcon( QIcon("img/none.jpg") )
 {
    _ui->setupUi(this);
    _ui->table->setIconSize(QSize(75, 75));
        
    writeTime(0);
        
    Clip c1("img/tweedy0.jpg" );
    c1.setPosition(0,2);
    Clip c2( "img/tweedy1.jpg" );
    c2.setPosition(2,3);
    Clip c3( "img/tweedy2.jpg" );
    c3.setPosition(3,6);
    Clip c4( "img/tweedy3.jpg" );
    c4.setPosition(6,8);
    _clips.push_back(c1);
    _clips.push_back(c2);
    _clips.push_back(c3);
    _clips.push_back(c4);
    
    /*QIcon icon( QString::fromStdString("img/none.jpg") );
    QTableWidgetItem *realTime = new QTableWidgetItem(icon,"");
    _ui->table->setItem(0, 0, realTime);*/
            
    drawMiniatures();
    
    connect(this, SIGNAL( valueChanged(unsigned int) ), this, SLOT(writeTime(unsigned int)) );
    connect( _timer, SIGNAL(timeout()), this, SLOT(increaseTime()) );
    connect( this->_ui->table , SIGNAL( cellClicked(int,int) ), this, SLOT( getCurrentTime(int,int)));
    
       
}



void TimeLine::drawMiniatures()
{
    char str[5];
    
    for (It it=_clips.begin(); it!=_clips.end(); ++it)
        for (int j=(*it).timeIn(); j<(*it).timeOut(); ++j)
        {
            _ui->table->insertColumn(j);
            sprintf (str, "%d", j);
            _ui->table->setHorizontalHeaderItem(j, new QTableWidgetItem( QString(str) ) );
            
            QIcon icon( QString::fromStdString((*it).imgPath().string()) );
            QTableWidgetItem *newItem = new QTableWidgetItem(icon,"");
            _ui->table->setItem(0, j, newItem);
          }
}


void TimeLine::increaseTime()
{
    if (_time < _ui->table->columnCount())
    {
        ++ _time;
        Q_EMIT valueChanged(_time);
        Q_EMIT displayChanged(_time, _clips);

    }
    else
        _timer->stop(); 

}

void TimeLine::writeTime(unsigned int newValue)
{
    _ui->time->setNum((int)newValue);
    _ui->table->setCurrentCell(0,(int)newValue);
    
}

void TimeLine::getCurrentTime(int row,int column)
{
    _time = column;
    //if (_time ==  _ui->table->columnCount() -1 )
    //  _time = -1;
    Q_EMIT valueChanged(_time);
    Q_EMIT displayChanged(_time, _clips);
}



void TimeLine::on_playButton_clicked()
{
   _timer->start(1000);
}


void TimeLine::on_pauseButton_clicked()
{
   _timer->stop(); 
        
}

void TimeLine::on_zeroButton_clicked()
{
   _time = 0;
   Q_EMIT valueChanged(_time);
   Q_EMIT displayChanged(_time, _clips);
}

void TimeLine::on_nextButton_clicked()
{
    for (It it=_clips.begin(); it!=_clips.end(); ++it)
    {
        if ( (*it).timeIn() > _time )
        {
            _time = (*it).timeIn();
            Q_EMIT valueChanged(_time);
            Q_EMIT displayChanged(_time, _clips);

            break;
        }
    }
}   

void TimeLine::on_prevButton_clicked()
{
    for (It it=_clips.end(); it!=_clips.begin(); --it)
    {
        if ( (*it).timeIn()!=0 &&(*it).timeIn() < _time )
        {
            _time = (*it).timeIn();
            Q_EMIT valueChanged(_time);
            Q_EMIT displayChanged(_time, _clips);

            break;
        }
    }
}

void TimeLine::on_addTimeButton_clicked()
{ 
    int current = _ui->table->columnCount();
    char str[3];
    
    for (int i=0;  i<_ui->spin->value(); ++i)
    {
        _ui->table->insertColumn(current + i);
        sprintf (str, "%d", current+i);
        _ui->table->setHorizontalHeaderItem(current+i, new QTableWidgetItem( QString(str) ) );
    }
            
}

void TimeLine::on_plusButton_clicked()
{ 
   if ( _ui->table->currentColumn() > -1 )
   {
       //add a column in current column
       int current = _ui->table->currentColumn();
       _ui->table->insertColumn( current+1 );
       
       //actualize horizontal header
       char str[3];
       for (int i=current ; i< _ui->table->columnCount(); ++i)
       {
           sprintf (str, "%d", i+1);
           _ui->table->setHorizontalHeaderItem(i+1, new QTableWidgetItem( QString(str) ) );
       }
       
       //actualize time in and time out of each clip following the current one
       It it;
       for (it=_clips.end(); it!=_clips.begin(); --it)
       {
           if ( (*it).timeIn() <= current)
               break;
           else
           {
               (*it).setTimeIn(1);
               (*it).setTimeOut(1);
           }
       }
       //increase time in of current clip
       (*it).setTimeOut(1);
       
       //add the icon in the new column
       QIcon icon( QString::fromStdString((*it).imgPath().string()) );
       QTableWidgetItem *newItem = new QTableWidgetItem(icon,"");
       _ui->table->setItem(0, current+1, newItem);
       
   }
   
}
   
      
       


void TimeLine::on_minusButton_clicked()
{ 
     if ( _ui->table->currentColumn() > -1 )
       {
           //remove the current column
           int current = _ui->table->currentColumn();
           //if (_ui->table->columnCount() > 1)
           _ui->table->removeColumn( current );
                    
           char str[3];

           //actualize horizontal header after removing the current one
           for (int i=current ; i< _ui->table->columnCount(); ++i)
           {
               sprintf (str, "%d", i);
               _ui->table->setHorizontalHeaderItem(i, new QTableWidgetItem( QString(str) ) );
           }

           //actualize time in and time out of each clip following the current one
           It it;
           for (it=_clips.end(); it!=_clips.begin(); --it)
           {
               if ( (*it).timeIn() <= current)
                   break;
               else
               {
                   (*it).setTimeIn(-1);
                   (*it).setTimeOut(-1);
               }
           }
                      
           //dicrease time out of current clip
           (*it).setTimeOut(-1);
           
           //delete clip if its length is 0 and signal a change of display           
           if ( (*it).timeIn() == (*it).timeOut() )
                _clips.erase(it);
                     
           //fix new selected item
           if (current < _clips.rbegin()->timeOut()-1)
                _ui->table->setCurrentCell(0,current);
           
           else
                _ui->table->setCurrentCell(0,_clips.rbegin()->timeOut()-1);
           
           
           Q_EMIT displayChanged(_time, _clips);
           
       }
}


TimeLine::~TimeLine() 
{
    delete _ui;
    delete _timer;
}

