#ifndef EXPORTWIDGET_HPP
#define EXPORTWIDGET_HPP

#include <QtGui/QWidget>

namespace Ui {
    class ExportWidget;
}

class ExportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExportWidget(QWidget *parent = 0);
    ~ExportWidget();

private:
    Ui::ExportWidget *ui;
};

#endif // EXPORTWIDGET_HPP
