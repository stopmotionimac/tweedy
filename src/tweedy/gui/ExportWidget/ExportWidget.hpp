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
    
    void generateEDLExport(std::string, int, int);
    std::string generateTimeData(int, int, int);

public Q_SLOTS:
    
    void on_searchFolderProjectButton_clicked();
    void on_exportButton_clicked();
    void on_cancelButton_clicked();

private:
    
    Ui::ExportWidget *_ui;
};

#endif // EXPORTWIDGET_HPP
