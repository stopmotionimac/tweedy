#ifndef ABOUTTWEEDY_HPP
#define ABOUTTWEEDY_HPP

#include <QtGui/QDialog>

namespace Ui {
    class AboutTweedy;
}

class AboutTweedy : public QDialog
{
    Q_OBJECT

public:
    explicit AboutTweedy(QWidget *parent);
    ~AboutTweedy();

private:
    Ui::AboutTweedy *_ui;
};

#endif // ABOUTTWEEDY_HPP
