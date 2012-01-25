#include "GlWidgetViewer.h"

GlWidgetViewer::GlWidgetViewer(QWidget* parent)
: QGLWidget(parent), _qImage(QImage("img/tweedy0.jpg"))
{
    
}

void GlWidgetViewer::initializeGL() 
{
    glEnable(GL_DEPTH_TEST);
    
}


void GlWidgetViewer::resizeGL(int w, int h) 
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void GlWidgetViewer::paintGL() 
{
   GLuint idTex = bindTexture(_qImage);
   drawTexture (QRect(QPoint(0,400), QPoint(400,0)), idTex);
   /* 
   glEnable(GL_TEXTURE_2D);
    
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   glPixelStorei(GL_PACK_ALIGNMENT, 1);
       
   GLuint idTex = bindTexture(_qImage);
   glGenTextures(1, &idTex);
   glBindTexture(GL_TEXTURE_2D, idTex);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
   glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, _qImage.width(), _qImage.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _qImage.bits());
      
   glBindTexture(GL_TEXTURE_2D, idTex);
   glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3f(0.0,400.0,0.0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(400.0,400.0,0.0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(400.0,0.0,0.0);
	glTexCoord2f(0.0,1.0);
        glVertex3f(0.0,1.0,0.0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);*/
}




