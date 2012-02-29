
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtDeclarative/QDeclarativeView>
#include "dummymodel.h"


class MainWidget : public QDeclarativeView
{
    Q_OBJECT;
public:
    MainWidget(QWidget* parent=0);
    ~MainWidget();
public Q_SLOTS:


private:
    QDeclarativeContext* m_context;
    DummyModel model;

};

#endif // MAINWIDGET_H

