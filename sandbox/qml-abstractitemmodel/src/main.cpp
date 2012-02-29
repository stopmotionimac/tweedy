
#include "model.h"
#include <QtGui/QApplication>

#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);
	QDeclarativeView viewer;

	AnimalModel model;
	model.addAnimal(Animal("Wolf", "Medium"));
	model.addAnimal(Animal("Polar bear", "Large"));
	model.addAnimal(Animal("Quoll", "Small"));

	viewer.rootContext()->setContextProperty("myModel", &model);
	viewer.setSource(QUrl::fromLocalFile("sandbox/qml-abstractitemmodel/src/qml/abstractitemmodel/view.qml"));
	
	model.addAnimal(Animal("Quoll2", "Small2"));

	viewer.show();

	return app.exec();
}

