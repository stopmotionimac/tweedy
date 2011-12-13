#include "UndoView.hpp"
#include <QtCore/QString>
#include <iostream>
#include <string>
#include <QtCore/QVariant>


UndoView::~UndoView(){
    delete this->cmdMan;
    delete this->undoGroup;
}

QIcon UndoView::cleanIcon() const{
    return this->icon;
}

void UndoView::setCleanIcon(const QIcon & icon){
    this->icon = icon;
}

QString	UndoView::getEmptyLabel () const{
    return this->emptyLabel;
}


void UndoView::setEmptyLabel( const QString & label ){
    this->emptyLabel=label ;
}

        
QUndoGroup * UndoView::group() const{
    return this->undoGroup;
}


std::stack<IUndoRedoCommand *>& UndoView::stack() const{
    return this->cmdMan->getUndoStack();
}


void UndoView::fillStringStack(){
            std::stack<IUndoRedoCommand*> copyUndoStack(this->cmdMan->getUndoStack());
            std::stack<IUndoRedoCommand*> copyRedoStack(this->cmdMan->getRedoStack());
            
            while(!copyUndoStack.empty()){
                std::cout << (*copyUndoStack.top()).getText() << std::endl;
                QString q;
                pileString.push(q.fromStdString((*copyUndoStack.top()).getText()));
                copyUndoStack.pop();
                
            }
            while(!copyRedoStack.empty()){
                std::cout << (*copyRedoStack.top()).getText() << std::endl;
                QString q;
                pileString.push(q.fromStdString((*copyRedoStack.top()).getText()));
                copyRedoStack.pop();
                
            }
}

void UndoView::fill(){
    this->fillStringStack();
    
    while(!pileString.empty()){
        this->addItem(pileString.top());
        pileString.pop();
    }
}


CommandManager* UndoView::getCmdMan(){
    return cmdMan;
}


UndoWidget::UndoWidget( UndoView * nundoView){
    
    
    dockLayout = new QVBoxLayout();
    
    addButton = new QPushButton("Ajouter");
    dltButton = new QPushButton("Retirer");
    
    undoButton = new QPushButton("Undo");
    redoButton = new QPushButton("Redo");
    
    
    
    undoView = nundoView;
    
    undoView->fill();
    
    
    /* A modifier/cleaner */
    
    QVariant* tempValue = new QVariant(undoView->getCmdMan()->getSomme().getSommeValue());
    
    labelSomme = new QLabel("Somme :" + tempValue->toString());
    
    dockLayout->addWidget(addButton);
    dockLayout->addWidget(dltButton);
    dockLayout->addWidget(undoButton);
    dockLayout->addWidget(redoButton);
    dockLayout->addWidget(undoView);
    
    dockLayout->addWidget(labelSomme);
    
    this->setLayout(dockLayout);
    
    connect(undoButton, SIGNAL(clicked()), this, SLOT(updateUndoLabelValue()));
    connect(redoButton, SIGNAL(clicked()), this, SLOT(updateRedoLabelValue()));
    
}

UndoWidget::~UndoWidget(){
    
    delete dockLayout;
    delete addButton;
    delete dltButton;
}


void UndoWidget::updateUndoLabelValue(){
    
    undoView->getCmdMan()->undo();
    
    
    QVariant* tempValue = new QVariant(undoView->getCmdMan()->getSomme().getSommeValue());
    
    
    labelSomme->setText("Somme :" + tempValue->toString());
}


void UndoWidget::updateRedoLabelValue(){
    
    undoView->getCmdMan()->redo();
    
    
    QVariant* tempValue = new QVariant(undoView->getCmdMan()->getSomme().getSommeValue());
    
    
    labelSomme->setText("Somme :" + tempValue->toString());
}