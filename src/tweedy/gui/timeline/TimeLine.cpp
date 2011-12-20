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
    _ui(new Ui::TimeLine)
 {
    _ui->setupUi(this);
    
    
    Clip c1("img/tweedy0.jpg");
    c1.setPosition(0,2);
    Clip c2("img/tweedy1.jpg");
    c2.setPosition(3,4);
    Clip c3("img/tweedy2.jpg");
    c3.setPosition(4,6);
    Clip c4("img/tweedy3.jpg");
    c4.setPosition(7,9);
    _clips.push_back(c1);
    _clips.push_back(c2);
    _clips.push_back(c3);
    _clips.push_back(c4);
    
    drawMiniatures();
    
    connect(this, SIGNAL( valueChanged(unsigned int) ), this, SLOT(writeTime(unsigned int)) );
    connect( _timer, SIGNAL(timeout()), this, SLOT(increaseTime()) );
   
}



void TimeLine::drawMiniatures()
{
    for (It it=_clips.begin(); it!=_clips.end(); ++it)
    {
        for (int j=(*it).timeIn(); j<(*it).timeOut(); ++j)
        {
            QIcon icon((*it).imgPath());
            _ui->table->setIconSize(QSize(75, 75));
            _ui->table->item(0,j)->setIcon(icon);
        }
        std::cout<<std::endl;
    }
}


void TimeLine::increaseTime()
{
    ++ _time;
    Q_EMIT valueChanged(_time);

}

void TimeLine::writeTime(unsigned int newValue)
{
    _ui->time->setNum((int)newValue);
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
}

/*void TimeLine::on_nextButton_clicked()
{
   
}   

void TimeLine::on_previousButton_clicked()
{
   
}*/

void TimeLine::on_addButton_clicked(){ 
    int i = _ui->table->rowCount();
    if (i < 5)
    {
        
        char str[10];
        sprintf (str, "piste %d", i+1);
        
        _ui->table->insertRow(i);
        _ui->table->setVerticalHeaderItem(i, new QTableWidgetItem( QString(str) ) );
        
        
    }
}

void TimeLine::on_delButton_clicked(){ 
    
    int n = _ui->table->rowCount();
    if ( n > 1)
    {
        int c = _ui->table->currentRow();
        _ui->table->removeRow(c);
        char str[10];
        for (int i=c;i<n; ++i)
        {
            sprintf (str, "piste %d", n-1);
            _ui->table->setVerticalHeaderItem(i, new QTableWidgetItem( QString(str) ) );
        }
    }
}




TimeLine::~TimeLine() 
{
    delete _ui;
    delete _timer;
}

