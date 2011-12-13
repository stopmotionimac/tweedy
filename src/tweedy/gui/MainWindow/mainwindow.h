#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
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

private:
    Ui::MainWindow *ui;
    TimeSheet* timesheet;
    ViewerImg* viewerImg;
};

#endif // MAINWINDOW_H
