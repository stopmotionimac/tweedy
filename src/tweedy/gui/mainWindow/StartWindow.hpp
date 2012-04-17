#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QtGui/QDialog>
#include <QtGui/QToolButton>
#include <QtGui/QListWidget>

namespace Ui {
    class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();
    QToolButton* getNewProjectButton();
    QToolButton* getOpenProjectButton();
    QListWidget* getListRecentsProjects();

private:
    Ui::StartWindow *_ui;

};

#endif // STARTWINDOW_H
