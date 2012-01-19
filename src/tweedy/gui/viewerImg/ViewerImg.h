/* 
 * File:   ViewerImg.h
 * Author: julien
 *
 * Created on 13 décembre 2011, 23:05
 */

#ifndef _VIEWERIMG_H
#define	_VIEWERIMG_H

#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include "../timeline/TimeLineUi.h"
#include <QtGui/QPushButton>



class ViewerImg : public QWidget {
    Q_OBJECT
public:
    ViewerImg();
    ~ViewerImg();

    QLabel* labelImg(){ return _labelImg; }

private Q_SLOTS:
    void displayImg(std::string filename);    
    
private:
    QLabel* _labelImg;

public:
    QPushButton * _capture;
    //QAction * _captureAction;

};

#endif	/* _VIEWERIMG_H */

       
