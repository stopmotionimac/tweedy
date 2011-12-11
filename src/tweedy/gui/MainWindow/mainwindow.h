#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QLabel>
#include <QtGui/QListWidgetItem>


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
    QLabel *imageLabel;
};

#endif // MAINWINDOW_H
