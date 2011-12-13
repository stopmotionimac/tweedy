#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QLabel>
#include <QtGui/QListWidgetItem>
#include <QtGui/QListWidget>


#include "../timesheet/TimeSheet.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void on_photo_selected(QListWidgetItem * item);

    void on_ImportButton_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    TimeSheet* timesheet;
    QListWidget * listWidget;
};

#endif // MAINWINDOW_H
