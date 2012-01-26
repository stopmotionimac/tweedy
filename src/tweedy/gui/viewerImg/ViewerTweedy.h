#ifndef VIEWERTWEEDY_H
#define VIEWERTWEEDY_H

#include <QtGui/QWidget>
#include <QtGui/QToolButton>
#include <QtGui/QLabel>

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
    QLabel * getViewerLabel();

private Q_SLOTS:
    void displayImg(std::string filename);

private:
    Ui::ViewerTweedy *_ui;
};

#endif // VIEWERTWEEDY_H
