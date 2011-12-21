/* 
 * File:   ViewerImg.h
 * Author: julien
 *
 * Created on 13 décembre 2011, 23:05
 */

#ifndef _VIEWERIMG_H
#define	_VIEWERIMG_H

#include <QtGui/QLabel>
#include <QtGui/QDockWidget>
#include "../timeline/TimeLine.h"


class ViewerImg : public QDockWidget {
    Q_OBJECT
public:
    ViewerImg();
    ~ViewerImg();

    QLabel* labelImg(){ return _labelImg; }

private Q_SLOTS:
    void displayImg(unsigned int newValue, listC clips);    
    
private:
    QLabel* _labelImg;
};

#endif	/* _VIEWERIMG_H */

       