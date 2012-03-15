
#include "MyQmlWrapper.hpp"

#include <qobjectlistmodel.h>

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeProperty>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>



int main(int argc, char ** argv)
{
	MyQmlWrapper qmlWrapper;
	// Prepare datas
	qmlWrapper.getMyModel()->append( new MyDataObject("A1", "B1") );
	qmlWrapper.getMyModel()->append( new MyDataObject("A2", "B2") );
	qmlWrapper.getMyModel()->append( new MyDataObject("A3", "B3") );
	qmlWrapper.getMyModel()->append( new MyDataObject("A4", "B4") );
	
	// declare the new type to qml
	qmlRegisterType<QObjectListModel>();
	
	// Our application
	QApplication app(argc, argv);
	QMainWindow mainWindow;
	QWidget* mainWidget = new QWidget( &mainWindow );
	mainWindow.setCentralWidget( mainWidget );
	QVBoxLayout* mainVLayout = new QVBoxLayout( mainWidget );
	
	{
		// Create our declarative view
		QDeclarativeView* viewer = new QDeclarativeView( mainWidget );
		viewer->setResizeMode(QDeclarativeView::SizeRootObjectToView);
		//viewer->rootContext()->setContextProperty( "myModel", &model );
		viewer->rootContext()->setContextProperty( "myQmlWrapper", &qmlWrapper );
		viewer->setSource(QUrl::fromLocalFile("sandbox/qml-objectlist/src/myView.qml"));
		// put it in the window
		mainVLayout->addWidget( viewer );
	}
	{
		QPushButton* pushButton = new QPushButton( "Modify Qml Datas", mainWidget );
		QObject::connect( pushButton, SIGNAL(clicked()), &qmlWrapper, SLOT(modifyQmlData()));
		mainVLayout->addWidget( pushButton );
	}
	
	mainWidget->setLayout( mainVLayout );
	
	mainWindow.show();
	return app.exec();
}

