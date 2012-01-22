#include "TimeSheet.h"
#include <QtGui/QTableView>
#include <QtGui/QIcon>
#include <iostream>
//#include <qt4/QtGui/qtablewidget.h>
#include <iostream>
//#include <qt4/QtGui/qlabel.h>
#include <QtGui/qtablewidget.h>
#include <QtGui/qlabel.h>

TimeSheet::TimeSheet(ViewerImg* vi, QDockWidget *parent) :
    QDockWidget(parent),
    currentTime(0),
    ui(new Ui::TimeSheet),
    timer(new QTimer(this)),
    viewerImg(new ViewerImg)
{
    ui->setupUi(this);
       
    viewerImg = vi;
    QIcon icon0("img/tweedy0.jpg");
    QIcon icon1("img/tweedy1.jpg");
    QIcon icon2("img/tweedy2.jpg");
    QIcon icon3("img/tweedy3.jpg");
    ui->maTable->item(0,0)->setIcon(icon0);
    ui->maTable->item(0,1)->setIcon(icon1);
    ui->maTable->item(0,2)->setIcon(icon2);
    ui->maTable->item(0,3)->setIcon(icon3);
    ui->maTable->item(1,0)->setText("img/tweedy0.jpg");
    ui->maTable->item(1,1)->setText("img/tweedy1.jpg");
    ui->maTable->item(1,2)->setText("img/tweedy2.jpg");
    ui->maTable->item(1,3)->setText("img/tweedy3.jpg");
    
    
    
   //for(int i=0; i<4; ++i)
     //  ui->maTable->item(1,0)->setText(ui->maTable->item(0,0)->icon().name());
       
            
    connect(timer, SIGNAL(timeout()), this, SLOT(on_playButton_clicked()));
            
}

void TimeSheet::on_playButton_clicked()
{
   timer->start(1000);
   ++currentTime;
   
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
           
           QPixmap current(ui->maTable->item(1,i)->text());
           current = current.scaled(300,200);
           
           viewerImg->labelImg()->setPixmap(current);
           viewerImg->labelImg()->adjustSize();
                      
            break;
       }
       
       if( !found )
       {
           ui->element->setText("none");
           viewerImg->labelImg()->clear();
       }
   }
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
    delete viewerImg;
    delete timer;
    delete ui;
}
