#include "ui_NewProjectWindow.h"

#include "NewProjectWindow.hpp"


newProjectWindow::newProjectWindow( QWidget *parent )
: QDialog( parent )
, _ui( new Ui::newProjectWindow )
{
	_ui->setupUi( this );

	setWindowTitle( tr( "Create a new project" ) );
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
