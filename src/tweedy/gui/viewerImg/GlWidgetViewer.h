#ifndef GLWIDGETVIEWER_H
#define GLWIDGETVIEWER_H

#include <QtOpenGL/QGLWidget>
#include <iostream>

class GlWidgetViewer : public QGLWidget
{
public:
    GlWidgetViewer(QWidget* parent);
    
    void setImgtoDisplay(const QImage& qImage) { _qImage = qImage; }
    
    
    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();
    
    /*void glDraw(){}
    void glInit(){}
    void initializeOverlayGL(){}
    void paintOverlayGL(){}
    void resizeOverlayGL( int width, int height ){}*/
    
    
private:
    QImage _qImage;
        
    
    
};

#endif // GLWIDGETVIEWER_H
