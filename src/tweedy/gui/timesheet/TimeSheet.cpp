#include "TimeSheet.h"
#include "ui_TimeSheet.h"
#include <QtGui/QTableView>
//#include <QtGui/QObject>

#include <iostream>


TimeSheet::TimeSheet(QWidget *parent) :
    QWidget(parent),
    currentTime(-1),
    ui(new Ui::TimeSheet)
{
    ui->setupUi(this);
    ui->temps->setNum(currentTime + 1);
    
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_playButton_clicked()));
            
}

void TimeSheet::on_playButton_clicked()
{
   timer->start(1000);
   ++TimeSheet::currentTime;
   
   ui->temps->setNum(currentTime);
   
   for (int i = 0;i<4;i++)
   {
       if (currentTime >= ui->maTable->item(i,1)->text().toInt())
                    ui->element->setText(ui->maTable->item(i,0)->text());
   }
    
         
}

void TimeSheet::on_pauseButton_clicked()
{
   timer->stop(); 
        
}



TimeSheet::~TimeSheet()
{
    delete ui;
}