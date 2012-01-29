#include "newprojectwindow.h"
#include "ui_newprojectwindow.h"

newProjectWindow::newProjectWindow(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::newProjectWindow)
{
    _ui->setupUi(this);

    setWindowTitle(tr("Creer un nouveau projet"));
}

QToolButton * newProjectWindow::getSearchFolderProjectButton()
{
    return _ui->searchFolderProjectButton;
}

QLineEdit * newProjectWindow::getFolderProjectLineEdit()
{
    return _ui->folderProjectLineEdit;
}

newProjectWindow::~newProjectWindow()
{
    delete _ui;
}
