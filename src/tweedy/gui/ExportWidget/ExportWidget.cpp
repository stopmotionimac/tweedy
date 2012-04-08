#include "ExportWidget.hpp"
#include "ui_ExportWidget.h"

ExportWidget::ExportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExportWidget)
{
    ui->setupUi(this);
}

ExportWidget::~ExportWidget()
{
    delete ui;
}
