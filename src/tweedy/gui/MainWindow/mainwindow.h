#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
<<<<<<< HEAD
#include <QtGui/QLabel>
#include <QtGui/QListWidgetItem>

=======
#include "../timesheet/TimeSheet.h"
>>>>>>> c6c92d07f7a26c0ff557cd51658186a94fa97790

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

private:
    Ui::MainWindow *ui;
<<<<<<< HEAD
    QLabel *imageLabel;
=======
    TimeSheet* timesheet;
>>>>>>> c6c92d07f7a26c0ff557cd51658186a94fa97790
};

#endif // MAINWINDOW_H
