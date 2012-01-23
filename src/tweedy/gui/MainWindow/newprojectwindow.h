#ifndef NEWPROJECTWINDOW_H
#define NEWPROJECTWINDOW_H

#include <QtGui/QDialog>

namespace Ui {
    class newProjectWindow;
}

class newProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit newProjectWindow(QWidget *parent = 0);
    ~newProjectWindow();

private:
    Ui::newProjectWindow *ui;
};

#endif // NEWPROJECTWINDOW_H
