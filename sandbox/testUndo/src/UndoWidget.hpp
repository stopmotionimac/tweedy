#ifndef UNDOWIDGET_HPP
#define	UNDOWIDGET_HPP

#include "UndoView.hpp"

#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>


class UndoWidget: public QWidget{
    Q_OBJECT
public:
     
    UndoWidget(UndoView * undoView);
    ~UndoWidget();

private Q_SLOTS:
    void updateUndoLabelValue();
    void updateRedoLabelValue();
    void addCmdInStack();
    
    
private:
    
    QVBoxLayout * dockLayout;
    
    QPushButton * addButton;
    QPushButton * undoButton;
    QPushButton * redoButton;
    
    QLabel * labelSomme;
    
    UndoView* undoView;
};

#endif	/* UNDOWIDGET_HPP */

