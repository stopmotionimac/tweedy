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


class ViewerImg : public QDockWidget {
    Q_OBJECT
public:
    ViewerImg();
    ~ViewerImg();

    QLabel* labelImg(){ return _labelImg; }
   
private:
    QLabel* _labelImg;
};

#endif	/* _VIEWERIMG_H */

       