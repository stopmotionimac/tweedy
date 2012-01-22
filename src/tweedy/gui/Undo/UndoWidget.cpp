#include "UndoWidget.hpp"



UndoWidget::UndoWidget( UndoView * undoView){
    
    
    dockLayout = new QVBoxLayout(this);
    
    //addButton = new QPushButton("Ajouter Commande",this);
    
    undoButton = new QPushButton("Undo",this);
    redoButton = new QPushButton("Redo",this);
    
    
    
    _undoView = undoView;
    
    _undoView->fill();
    
    
    /* A modifier/cleaner */
    
    //QVariant* tempValue = new QVariant();
    
    //labelSomme = new QLabel("Somme :" + tempValue->toString(),this);
    
    //dockLayout->addWidget(addButton);
    dockLayout->addWidget(undoButton);
    dockLayout->addWidget(redoButton);
    dockLayout->addWidget(_undoView);
    
    //dockLayout->addWidget(labelSomme);
    
    this->setLayout(dockLayout);
    
    connect(undoButton, SIGNAL(clicked()), this, SLOT(updateUndoLabelValue()));
    connect(redoButton, SIGNAL(clicked()), this, SLOT(updateRedoLabelValue()));
    //connect(addButton, SIGNAL(clicked()), this, SLOT(addCmdInStack()));
    
}

UndoWidget::~UndoWidget(){

}


void UndoWidget::updateUndoLabelValue(){
    
    std::cout << "undo action" << std::endl;
    
    _undoView->getCmdMan()->undo();
    _undoView->fill();
    
    //QVariant* tempValue = new QVariant(undoView->getSomme().getSommeValue());
    
    
    //labelSomme->setText("Somme :" + tempValue->toString());
    
    
}


void UndoWidget::updateRedoLabelValue(){
    
    std::cout << "redo action" << std::endl;

    
    _undoView->getCmdMan()->redo();
    _undoView->fill();
    
    //QVariant* tempValue = new QVariant(undoView->getSomme().getSommeValue());
    
    
    //labelSomme->setText("Somme :" + tempValue->toString());
    
    
}

/*
void UndoWidget::addCmdInStack(){
    
    //IUndoRedoCommand * cmd = new AddCommand(4000,"AddCommand +4000",undoView->getSomme());
    
    undoView->getCmdMan()->pushNewCommand(cmd);
    undoView->fill();
    
    QVariant* tempValue = new QVariant(undoView->getSomme().getSommeValue());
    
    
    labelSomme->setText("Somme :" + tempValue->toString()); 
}
*/