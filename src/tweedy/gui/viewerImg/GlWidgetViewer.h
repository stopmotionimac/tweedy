#ifndef GLWIDGETVIEWER_H
#define GLWIDGETVIEWER_H

#include <QtOpenGL/QGLWidget>

class GlWidgetViewer : public QGLWidget
{
public:
    GlWidgetViewer(QWidget* parent);
    
    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();
    void setImgtoDisplay(const QPixmap& pixmap);
    
private:
    QPixmap _imgToDisplay;
        
    
    
};

#endif // GLWIDGETVIEWER_H
