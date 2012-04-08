#include "ui_ExportWidget.h"

#include <tweedy/gui/export/ExportWidget.hpp>

ExportWidget::ExportWidget( QWidget *parent ) : QWidget( parent )
        , _ui( new Ui::ExportWidget )
{
    //_ui->setupUi( this );
}

ExportWidget::~ExportWidget()
{
    //delete _ui ;
}
