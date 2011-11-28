#ifndef TIMESHEET_H
#define TIMESHEET_H

#include <QtGui/QWidget>
#include <QtGui/QStandardItemModel>
#include <QtCore/QTimer>
#include <string>

namespace Ui {
    class TimeSheet;
}

class TimeSheet : public QWidget
{
    Q_OBJECT

public:
    explicit TimeSheet(QWidget *parent = 0);
    ~TimeSheet();
       
private Q_SLOTS:
    void on_playButton_clicked();
    void on_pauseButton_clicked();

private:
    Ui::TimeSheet *ui;
    int currentTime;
    QTimer * timer;
};

#endif // TIMESHEET_H

