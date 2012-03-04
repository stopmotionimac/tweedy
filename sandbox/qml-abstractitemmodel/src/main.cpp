
#include "model.h"
#include "MyQmlWrapper.hpp"

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

	qmlRegisterType<AnimalModel>();
	
	MyQmlWrapper qmlWrapper;
	
	qmlWrapper.getAnimalModel()->addAnimal( Animal("Wolf", "Medium") );
	qmlWrapper.getAnimalModel()->addAnimal( Animal("Polar bear", "Large") );
	qmlWrapper.getAnimalModel()->addAnimal( Animal("Quoll", "Small") );

    viewer.setResizeMode(QDeclarativeView::SizeRootObjectToView);
	
//	viewer.rootContext()->setContextProperty( "myModel", &model );
	viewer.rootContext()->setContextProperty( "myQmlWrapper", &qmlWrapper );
	
	viewer.setSource(QUrl::fromLocalFile("sandbox/qml-abstractitemmodel/src/qml/abstractitemmodel/view.qml"));
	
	qmlWrapper.getAnimalModel()->addAnimal( Animal("Quoll2", "Small2") );

	viewer.show();

	return app.exec();
}

