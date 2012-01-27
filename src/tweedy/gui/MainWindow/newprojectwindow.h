#ifndef NEWPROJECTWINDOW_H
#define NEWPROJECTWINDOW_H

#include <QtGui/QDialog>
#include <QtGui/QToolButton>
#include <QtGui/QLineEdit>

namespace Ui {
    class newProjectWindow;
}

class newProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit newProjectWindow(QWidget *parent);
    ~newProjectWindow();

    QToolButton * getSearchFolderProjectButton();
    QLineEdit * getFolderProjectLineEdit();

private:
    Ui::newProjectWindow *_ui;
};

#endif // NEWPROJECTWINDOW_H
