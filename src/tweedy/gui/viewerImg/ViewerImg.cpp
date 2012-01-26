#include <QtGui/QPushButton>

#include "ViewerImg.h"



ViewerImg::ViewerImg( QWidget* parent ) : QWidget(parent), _labelImg(new QLabel(this)), _qGlViewer(new GlWidgetViewer(this))
{
    setWindowTitle("Visualisation");
    _labelImg->setScaledContents(true);
    
    //creation des boutons du viewer
    _capture = new QToolButton(this);

    QVBoxLayout * layoutWidget = new QVBoxLayout(this);
    //layoutWidget->addWidget(_labelImg);
    layoutWidget->addWidget(_qGlViewer);
    
    layoutWidget->addWidget(_capture);
    setLayout(layoutWidget);

}

void ViewerImg::displayImg(std::string filename)
{
   _qGlViewer->setImgtoDisplay(QImage(QString::fromStdString(filename)));
   _qGlViewer->paintGL();
   _labelImg->setPixmap(QPixmap(QString::fromStdString(filename)));
}  


ViewerImg::~ViewerImg() 
{
    delete _labelImg;
    delete _capture;
}
