#include "TimeSheet.h"
#include <QtGui/QTableView>
#include <iostream>


TimeSheet::TimeSheet(QDockWidget *parent) :
    QDockWidget(parent),
    currentTime(-1),
    ui(new Ui::TimeSheet),
    timer(new QTimer(this))
{
    ui->setupUi(this);
    ui->temps->setNum(currentTime + 1);
    
    connect(timer, SIGNAL(timeout()), this, SLOT(on_playButton_clicked()));
            
}


void TimeSheet::on_playButton_clicked()
{
   timer->start(1000);
   ++TimeSheet::currentTime;
   
   ui->temps->setNum(currentTime);
   
   bool found = false;
   for (int i=0; i<4; ++i)
   {
       if ( currentTime >= ui->maTable->item(2,i)->text().toInt() &&
            currentTime < ui->maTable->item(3,i)->text().toInt() )
       {
           found = true;
            ui->element->setText(ui->maTable->item(1,i)->text());
            ui->maTable->setCurrentCell(0,i);
            break;
       }
   }

   if( !found )
       ui->element->setText("none");
         
}

void TimeSheet::on_pauseButton_clicked()
{
   timer->stop(); 
        
}

void TimeSheet::on_zeroButton_clicked()
{
   currentTime = 0;
   ui->temps->setNum(currentTime);
        
}

void TimeSheet::on_nextButton_clicked()
{
    bool found = false;
    int selectedRow;
    
    while (true)
    {
        currentTime ++;
        for(int i=0; i<4; i++)
        {
            if ( i!=3 )
            {
                if ( currentTime >= ui->maTable->item(2,i)->text().toInt() && currentTime <= ui->maTable->item(2,i+1)->text().toInt() )
                {
                    selectedRow = i+1;
                    found = true;
                    break;
                }
            }
            else 
                if ( currentTime >= ui->maTable->item(2,i)->text().toInt() )
                {
                    selectedRow = 0;
                    found = true;
                    break;
                }
        }
    
        if (found)
        {
            currentTime = ui->maTable->item(2,selectedRow)->text().toInt();
            ui->maTable->setCurrentCell(0, selectedRow);
            ui->temps->setNum(currentTime);
            ui->element->setText(ui->maTable->item(1,selectedRow)->text());
            break;
        }
    }
}   

void TimeSheet::on_previousButton_clicked()
{
   bool found = false;
    int selectedRow;
    
    while (true)
    {
        currentTime--;
        for(int i=0; i<4; i++)
        {
            if ( i!=0 )
            {
                if ( currentTime < ui->maTable->item(3,i)->text().toInt() && currentTime > ui->maTable->item(3,i-1)->text().toInt() )
                {
                    selectedRow = i;
                    found = true;
                    break;
                }
            }
            else 
                if ( currentTime <= ui->maTable->item(3,0)->text().toInt() )
                {
                    selectedRow = 3;
                    found = true;
                    break;
                }
        }
    
        if (found)
        {
            currentTime = ui->maTable->item(2,selectedRow)->text().toInt();
            ui->maTable->setCurrentCell(0, selectedRow);
            ui->temps->setNum(currentTime);
            ui->element->setText(ui->maTable->item(1,selectedRow)->text());
            break;
        }
    }
}


TimeSheet::~TimeSheet()
{
	delete timer;
    delete ui;
}
