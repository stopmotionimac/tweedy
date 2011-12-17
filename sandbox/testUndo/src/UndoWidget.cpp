#include "UndoWidget.hpp"



UndoWidget::UndoWidget( UndoView * nundoView){
    
    
    dockLayout = new QVBoxLayout(this);
    
    addButton = new QPushButton("Ajouter Commande",this);
    
    undoButton = new QPushButton("Undo",this);
    redoButton = new QPushButton("Redo",this);
    
    
    
    undoView = nundoView;
    
    undoView->fill();
    
    
    /* A modifier/cleaner */
    
    QVariant* tempValue = new QVariant(undoView->getCmdMan()->getSomme().getSommeValue());
    
    labelSomme = new QLabel("Somme :" + tempValue->toString(),this);
    
    dockLayout->addWidget(addButton);
    dockLayout->addWidget(undoButton);
    dockLayout->addWidget(redoButton);
    dockLayout->addWidget(undoView);
    
    dockLayout->addWidget(labelSomme);
    
    this->setLayout(dockLayout);
    
    connect(undoButton, SIGNAL(clicked()), this, SLOT(updateUndoLabelValue()));
    connect(redoButton, SIGNAL(clicked()), this, SLOT(updateRedoLabelValue()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addCmdInStack()));
    
}

UndoWidget::~UndoWidget(){

}


void UndoWidget::updateUndoLabelValue(){
    
    undoView->getCmdMan()->undo();
    undoView->fill();
    
    QVariant* tempValue = new QVariant(undoView->getCmdMan()->getSomme().getSommeValue());
    
    
    labelSomme->setText("Somme :" + tempValue->toString());
    
    
}


void UndoWidget::updateRedoLabelValue(){
    
    undoView->getCmdMan()->redo();
    undoView->fill();
    
    QVariant* tempValue = new QVariant(undoView->getCmdMan()->getSomme().getSommeValue());
    
    
    labelSomme->setText("Somme :" + tempValue->toString());
    
    
}


void UndoWidget::addCmdInStack(){
    
    IUndoRedoCommand * cmd = new AddCommand(4000,"AddCommand +4000",undoView->getCmdMan()->getSomme());
    
    undoView->getCmdMan()->pushNewCommand(cmd);
    undoView->fill();
    
    QVariant* tempValue = new QVariant(undoView->getCmdMan()->getSomme().getSommeValue());
    
    
    labelSomme->setText("Somme :" + tempValue->toString());
}
