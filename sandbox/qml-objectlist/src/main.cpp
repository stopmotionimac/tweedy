
#include "MyQmlWrapper.hpp"

#include <qobjectlistmodel.h>

#include <QtGui/QApplication>

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeProperty>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	QDeclarativeView viewer;

	qmlRegisterType<QObjectListModel>();
	
	MyQmlWrapper qmlWrapper;
	
	qmlWrapper.getMyModel()->append( new MyDataObject("A1", "B1") );
	qmlWrapper.getMyModel()->append( new MyDataObject("A2", "B2") );
	qmlWrapper.getMyModel()->append( new MyDataObject("A3", "B3") );

    viewer.setResizeMode(QDeclarativeView::SizeRootObjectToView);
	
//	viewer.rootContext()->setContextProperty( "myModel", &model );
	viewer.rootContext()->setContextProperty( "myQmlWrapper", &qmlWrapper );
	
	viewer.setSource(QUrl::fromLocalFile("sandbox/qml-objectlist/src/myView.qml"));
	
	qmlWrapper.getMyModel()->append( new MyDataObject("A4", "B4") );

	viewer.show();

	return app.exec();
}

