#include "UndoWidget.hpp"



UndoWidget::UndoWidget( UndoView * undoView){
    
    
    dockLayout = new QVBoxLayout(this);
    
    undoButton = new QPushButton("Undo",this);
    redoButton = new QPushButton("Redo",this);
    
    
    
    _undoView = undoView;
    
    _undoView->fill();
    
    
    /* A modifier/cleaner */
    
    dockLayout->addWidget(undoButton);
    dockLayout->addWidget(redoButton);
    dockLayout->addWidget(_undoView);
    
    
    this->setLayout(dockLayout);
    
    connect(undoButton, SIGNAL(clicked()), this, SLOT(updateUndoLabelValue()));
    connect(redoButton, SIGNAL(clicked()), this, SLOT(updateRedoLabelValue()));
    
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