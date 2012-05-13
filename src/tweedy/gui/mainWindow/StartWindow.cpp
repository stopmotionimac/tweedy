#include "ui_StartWindow.h"

#include "StartWindow.hpp"
#include <tweedy/core/Projet.hpp>

#include <iostream>

StartWindow::StartWindow( QWidget *parent )
: QDialog( parent )
, _ui( new Ui::StartWindow )
{
	_ui->setupUi( this );

	setWindowTitle( tr( "TWEEDY - logiciel de stop motion" ) );

	_ui->logoLabel->setPixmap( QString::fromStdString( "img/logo.png" ) );
        

}

QToolButton* StartWindow::getNewProjectButton()
{
	return _ui->newProjectButton;
}

QToolButton* StartWindow::getOpenProjectButton()
{
	return _ui->openProjectButton;
}

QListWidget* StartWindow::getListRecentsProjects()
{
    return _ui->listRecentsProjects;
}



StartWindow::~StartWindow()
{
	delete _ui;
}
