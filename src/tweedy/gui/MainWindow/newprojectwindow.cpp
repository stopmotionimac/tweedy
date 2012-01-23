#include "newprojectwindow.h"
#include "ui_newprojectwindow.h"

newProjectWindow::newProjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newProjectWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Creer un nouveau projet"));
}

QToolButton * newProjectWindow::getSearchFolderProjectButton()
{
    return ui->searchFolderProjectButton;
}

QLineEdit * newProjectWindow::getFolderProjectLineEdit()
{
    return ui->folderProjectLineEdit;
}

newProjectWindow::~newProjectWindow()
{
    delete ui;
}
