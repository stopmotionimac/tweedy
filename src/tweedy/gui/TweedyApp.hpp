#ifndef TWEEDYAPP_HPP
#define	TWEEDYAPP_HPP

#include <QtGui/QApplication>

class TweedyApp : public QApplication
{
    
public:
        
    TweedyApp(int& argc, char** argv);
    ~TweedyApp();
    
    bool notify(QObject * receiver, QEvent * event);
    
};


#endif	/* TWEEDYAPP_HPP */

