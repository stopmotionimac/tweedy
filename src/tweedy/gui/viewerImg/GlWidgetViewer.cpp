#include "glwidgetviewer.h"

GlWidgetViewer::GlWidgetViewer(QWidget* parent)
: QGLWidget(parent)
{
    
}

void GlWidgetViewer::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void GlWidgetViewer::resizeGL( int width, int height )
{
    // setup viewport, projection etc.:
    glViewport(0, 0, (GLint)width, (GLint)height); 
}

void GlWidgetViewer::paintGL()
{
    gluOrtho2D( 0, 1, 0, 1 );
    glEnable(GL_TEXTURE_2D);
    
    GLuint idTex = bindTexture(_imgToDisplay);
    drawTexture( QRectF ( 0, 0, 1, 1 ), idTex );

    glDisable(GL_TEXTURE_2D);

}

void GlWidgetViewer::setImgtoDisplay(const QPixmap& pixmap)
{
    _imgToDisplay = pixmap;

}


