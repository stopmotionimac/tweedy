#include <tweedy/gui/TweedyApp.hpp>
#include <QtGui/QMessageBox>

TweedyApp::TweedyApp(int& argc, char** argv)
        :QApplication(argc,argv)
{
    
}

TweedyApp::~TweedyApp()
{
    
}

bool TweedyApp::notify(QObject * receiver, QEvent * event)
{
    static const QString msg( tr("The application has encountered an unexpected error."));
    try
    {
        return QApplication::notify(receiver, event);
    }
    catch ( const std::exception& e)
    {
        int r = QMessageBox::critical(0, tr("Tweedy"), tr("The application shuts down"),0,1,2);
    }
    catch( ... )
    {
        tr("Unknown exception");
    }
    return false;
}