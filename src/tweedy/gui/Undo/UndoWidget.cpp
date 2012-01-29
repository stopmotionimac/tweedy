#include "UndoWidget.hpp"



UndoWidget::UndoWidget( UndoView * undoView){
    
    
    _dockLayout = new QVBoxLayout(this);
    
    _undoButton = new QPushButton("Undo",this);
    _redoButton = new QPushButton("Redo",this);
    
    
    
    _undoView = undoView;
    
    _undoView->fill();
    
    
    /* A modifier/cleaner */
    
    _dockLayout->addWidget(_undoButton);
    _dockLayout->addWidget(_redoButton);
    _dockLayout->addWidget(_undoView);
    
    
    this->setLayout(_dockLayout);
    
    connect(_undoButton, SIGNAL(clicked()), this, SLOT(updateUndoLabelValue()));
    connect(_redoButton, SIGNAL(clicked()), this, SLOT(updateRedoLabelValue()));
    
}

UndoWidget::~UndoWidget(){

}


void UndoWidget::updateUndoLabelValue(){
    
    std::cout << "undo action" << std::endl;
    
    _undoView->getCmdMan().undo();
    
}


void UndoWidget::updateRedoLabelValue(){
    
    std::cout << "redo action" << std::endl;

    
    _undoView->getCmdMan().redo();
    
}