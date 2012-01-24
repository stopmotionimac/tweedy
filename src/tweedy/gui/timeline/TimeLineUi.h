#ifndef _TIMELINE_H
#define	_TIMELINE_H

#include <stdlib.h>
#include <list>
#include<cstdio>
#include<boost/format.hpp>
#include <QtCore/QTimer>

#include <QtGui/QDockWidget>
#include <QtGui/QApplication>
#include <QtGui/QIcon>
#include <QtGui/QToolBar>

#include <tweedy/core/Timeline.hpp>

#include "ui_TimeLineUi.h"


namespace Ui {
    class TimeLineUi : public Ui_Timeline {};
}

class TimeLineUi : public QDockWidget {
    Q_OBJECT
public:
    TimeLineUi(QDockWidget* parent=0);
    ~TimeLineUi();
    
    unsigned int time(){ return _time; }
    Ui::TimeLineUi* ui(){ return _ui; }
    Timeline* timeline(){return _timeline;}
    QIcon defautIcon(){return _defautIcon;}
        
    void createActions();
    void toolBar();
    void linkButtonsWithActions();
    
    void updateTable();
    void emitDisplayChanged();
    
                
public Q_SLOTS:
    void increaseTime();
    void writeTime(int newValue);
    void getCurrentTime(int row,int column);
    
    
    void handle_playAction_triggered();
    void handle_pauseAction_triggered();
    
    void handle_zeroAction_triggered();
    //void on_nextButton_clicked();
    //void on_prevButton_clicked();
    
    void handle_nextAction_triggered();
    void handle_prevAction_triggered();
    
    void handle_plusAction_triggered();
    void handle_minusAction_triggered();
    void handle_blankBeforeAction_triggered();
    void handle_blankAfterAction_triggered();
    void handle_deleteAction_triggered();
       
Q_SIGNALS:
    void timeChanged(int newValue);
    void displayChanged(std::string filename);
    
private:
    int _time;
    QTimer* _timer;
    Ui::TimeLineUi* _ui;
    Timeline* _timeline;
    QIcon _defautIcon;
    
    QAction * _playAction;
    QAction * _pauseAction;
    QAction * _nextAction;
    QAction * _prevAction;
    QAction * _zeroAction;
    
    QAction * _plusAction;
    QAction * _minusAction;
    QAction * _blankBeforeAction;
    QAction * _blankAfterAction;
    QAction * _deleteAction;
    
   
    
    
};

#endif	/* _TIMELINE_H */