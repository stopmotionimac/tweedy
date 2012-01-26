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
    QImage calculateImage(const QImage& sourceImage, const QImage& destinationImage);
    
private Q_SLOTS:
    void displayChanged(int time);
    void handle_onionAction_triggered();

private:
    Ui::ViewerTweedy *_ui;
    int _currentTime;
    QAction * _onionAction;
};

#endif // VIEWERTWEEDY_H
