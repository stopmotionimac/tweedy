#ifndef VIEWERTWEEDY_H
#define VIEWERTWEEDY_H

#include <QtGui/QWidget>
#include <QtGui/QToolButton>
#include <QtGui/QLabel>
#include <QtGui/QPainter>

namespace Ui {
    class ViewerTweedy;
}

class ViewerTweedy : public QWidget
{
    Q_OBJECT

public:
    explicit ViewerTweedy(QWidget *parent = 0);
    ~ViewerTweedy();
    QToolButton * getPlayPauseButton();
    QToolButton * getNextButton();
    QToolButton * getPreviousButton();
    QToolButton * getCaptureButton();
    QToolButton * getRetour0Button();
    QLabel * getViewerLabel();
    QLabel * getTimeLabel();

private Q_SLOTS:
    void displayChanged(int time);

private:
    Ui::ViewerTweedy *_ui;
};

#endif // VIEWERTWEEDY_H
