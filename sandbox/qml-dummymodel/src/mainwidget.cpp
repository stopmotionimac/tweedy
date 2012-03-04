
#include "mainwidget.h"

#include <QtDeclarative/QtDeclarative>
#include <QtDeclarative/QDeclarativeContext>

MainWidget::MainWidget(QWidget* parent) : QDeclarativeView(parent)
{
    setResizeMode(QDeclarativeView::SizeRootObjectToView);
    setMinimumSize(300,300);

    m_context=rootContext();
    m_context->setContextProperty("dummyModel", &model);
    setSource(QUrl("sandbox/qml-dummymodel/src/main.qml"));
}

MainWidget::~MainWidget()
{

}

