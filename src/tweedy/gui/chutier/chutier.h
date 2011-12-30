#ifndef CHUTIER_H
#define CHUTIER_H

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QListWidgetItem>
#include <QtGui/QAction>

#include "listwidget.h"

class Chutier : public QWidget
{
    Q_OBJECT

public:
    explicit Chutier(QWidget *parent = 0);
    ~Chutier();

public Q_SLOTS:
    void on_photo_selected(QListWidgetItem * item);
    void on_importButton_clicked();
    void on_deleteButton_clicked();

private:
    ListWidget * listWidget;

    QPushButton * importButton;
    QPushButton * deleteButton;

    QLabel * viewerChutier;

};

#endif // CHUTIER_H
