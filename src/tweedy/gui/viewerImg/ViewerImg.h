#ifndef _VIEWERIMG_H
#define	_VIEWERIMG_H

#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include <tweedy/gui/timeline/TimeLineUi.h>
#include <QtGui/QToolButton>



class ViewerImg : public QWidget {
    Q_OBJECT
public:
    ViewerImg( QWidget* parent );
    ~ViewerImg();

    QLabel* labelImg(){ return _labelImg; }
    

private Q_SLOTS:
    void displayImg(std::string filename);
    void displayChanged(int time);
    
private:
    QLabel* _labelImg;
    
public:
    QToolButton * _capture;
    QToolButton * _playButton;
    QToolButton * _nextButton;
    QToolButton * _previousButton;

};

#endif	/* _VIEWERIMG_H */
