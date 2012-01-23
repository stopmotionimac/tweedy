#ifndef _VIEWERIMG_H
#define	_VIEWERIMG_H

#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <tweedy/gui/timeline/TimeLineUi.h>
#include <QtGui/QToolButton>



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
    QToolButton * _capture;

};

#endif	/* _VIEWERIMG_H */
