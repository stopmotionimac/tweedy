#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QListWidget>
#include <QtGui/QLabel>
#include "../timesheet/TimeSheet.h"
#include "../viewerImg/ViewerImg.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void on_photo_selected(QListWidgetItem * item);

private:
    Ui::MainWindow *ui;
    TimeSheet* timesheet;

    QListWidget * listWidget;
    QLabel *imageLabel;
    ViewerImg* viewerImg;

};

#endif // MAINWINDOW_H
