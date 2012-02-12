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
#include <QtGui/QLabel>


#include <tweedy/core/Timeline.hpp>

#include "ui_TimeLineUi.h"
#include "tabletimeline.h"


/*namespace Ui {
    class TimeLineUi : public Ui_Timeline {};
}*/

class TimeLineUi : public QWidget {

    Q_OBJECT

public:
    TimeLineUi(QWidget* parent);

    ~TimeLineUi();
    
    unsigned int time() { return _time; }
    Ui::Timeline* ui() { return _ui; }
    Timeline* getTimeline() { return _timeline; }
    QIcon defautIcon() { return _defautIcon; }
    QTableWidget * getTableWidget() { return _table; }
        
    void createActions();
    void toolBar();
    void linkButtonsWithActions();
    
    void updateTable();
    //void emitDisplayChanged();

    QAction * getPlayPauseAction() { return _playPauseAction; }
    QAction * getNextAction() { return _nextAction; }
    QAction * getPreviousAction() { return _prevAction; }
    QAction * getRetour0Action() { return _zeroAction; }

                
public Q_SLOTS:
    void increaseTime();
    //void writeTime(int newValue);
    void getCurrentTime(int row,int column);
    void changeFps(int value){ _fps = value;}
    
    
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
    Ui::Timeline* _ui;
    int _fps;
    int _time;
    QTimer* _timer;
    bool _isPlaying;
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
