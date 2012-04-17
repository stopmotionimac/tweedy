#include "ui_NewProjectWindow.h"

#include "NewProjectWindow.hpp"
#include <tweedy/core/Projet.hpp>

#include <QtGui/QMessageBox>


newProjectWindow::newProjectWindow( QWidget *parent )
: QDialog( parent )
, _ui( new Ui::newProjectWindow )
{
	_ui->setupUi( this );

	setWindowTitle( tr( "Create a new project" ) );
        
        connect(_ui->buttonBox, SIGNAL(accepted()), this, SLOT(on_accept_clicked()));
        connect(_ui->buttonBox, SIGNAL(rejected()), this, SLOT(on_reject_clicked()));
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

void newProjectWindow::on_accept_clicked()
{
    /*affecter un nom de fichier et de dossier au projet*/
    
    if(_ui->nameProjectLineEdit->text().isEmpty() || _ui->folderProjectLineEdit->text().isEmpty())
        QMessageBox::about(this, tr("Empty Path"), tr("Please, choose a folder and a name"));
    else
    {
        Projet & projet = Projet::getInstance();
        
        QString projectFolder = QString(_ui->folderProjectLineEdit->text());
        projet.setProjectFolder(projectFolder.toStdString());
        
        QString projectFile = QString(_ui->nameProjectLineEdit->text());
        projet.setProjectFile(projectFile.toStdString());
        
        std::cout << "Project File :" << projet.getProjectFile() << std::endl;
        std::cout << "Project Folder :" << projet.getProjectFolder() << std::endl;
    }
    
}

void newProjectWindow::on_reject_clicked()
{
    this->close();
}