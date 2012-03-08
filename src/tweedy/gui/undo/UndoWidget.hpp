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
    
    
private:
    
    QVBoxLayout * _dockLayout;
    QPushButton * _undoButton;
    QPushButton * _redoButton;
    
    UndoView* _undoView;
};

#endif	/* UNDOWIDGET_HPP */

