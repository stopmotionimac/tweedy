#ifndef _TIMELINE_H
#define	_TIMELINE_H

#include <stdlib.h>
#include <list>
#include <cstdio>
#include <boost/format.hpp>
#include <QtCore/QTimer>

#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QtGui/QIcon>
#include <QtGui/QShortcut>


#include <tweedy/core/Timeline.hpp>

#include "ui_TimeLineUi.h"
#include "tabletimeline.h"


namespace Ui {
    class TimeLineUi : public Ui_Timeline {};
}

class TimeLineUi : public QWidget
{
    Q_OBJECT

public:
    TimeLineUi(QWidget* parent=0);
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
    
    
    void handle_playPauseAction_triggered();
        
    void handle_zeroAction_triggered();
    
    void handle_nextAction_triggered();
    void handle_prevAction_triggered();
    
    void handle_plusAction_triggered();
    void handle_minusAction_triggered();
    void handle_blankBeforeAction_triggered();
    void handle_blankAfterAction_triggered();
    void deleteKey_activated();
       
Q_SIGNALS:
    void timeChanged(int newValue);
    void displayChanged(std::string filename);
    
private:
    int _time;
    bool _isPlaying;
    QTimer* _timer;
    Ui::TimeLineUi* _ui;
    Timeline* _timeline;
    QIcon _defautIcon;
    
    QAction * _playPauseAction;
    QAction * _nextAction;
    QAction * _prevAction;
    QAction * _zeroAction;
    
    QAction * _plusAction;
    QAction * _minusAction;
    QAction * _blankBeforeAction;
    QAction * _blankAfterAction;
    
    QShortcut * _deleteKey;  
    
    TableTimeline * _table;
    
};

#endif	/* _TIMELINE_H */
