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

public Q_SLOTS:
    
    void on_accept_clicked();
    void on_reject_clicked();
    
    
private:
    Ui::newProjectWindow *_ui;
};

#endif // NEWPROJECTWINDOW_H
