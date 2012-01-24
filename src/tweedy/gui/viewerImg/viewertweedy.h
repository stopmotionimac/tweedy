#ifndef VIEWERTWEEDY_H
#define VIEWERTWEEDY_H

#include <QtGui/QWidget>

namespace Ui {
    class ViewerTweedy;
}

class ViewerTweedy : public QWidget
{
    Q_OBJECT

public:
    explicit ViewerTweedy(QWidget *parent = 0);
    ~ViewerTweedy();

private:
    Ui::ViewerTweedy *ui;
};

#endif // VIEWERTWEEDY_H
