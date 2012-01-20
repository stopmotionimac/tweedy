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

#include <tweedy/core/Timeline.hpp>

#include "ui_TimeLineUi.h"

typedef std::list<Clip> listC;
typedef std::list<Clip>::iterator It;

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
    listC clips(){ return _clips; }
    
    void updateTable();
    void emitDisplayChanged();
    
                
private Q_SLOTS:
    void increaseTime();
    void writeTime(int newValue);
    void getCurrentTime(int row,int column);
    void on_playButton_clicked();
    void on_pauseButton_clicked();
    void on_zeroButton_clicked();
    void on_nextButton_clicked();
    void on_prevButton_clicked();
    
    void on_plusButton_clicked();
    void on_minusButton_clicked();
    void on_blankBeforeButton_clicked();
    void on_blankAfterButton_clicked();
    void on_deleteButton_clicked();
       
Q_SIGNALS:
    void timeChanged(int newValue);
    void displayChanged(std::string filename);
    
private:
    QTableWidget* _table;
    int _time;
    QTimer* _timer;
    Ui::TimeLineUi* _ui;
    Timeline* _timeline;
    listC _clips;
    QIcon _defautIcon;
    
};

#endif	/* _TIMELINE_H */