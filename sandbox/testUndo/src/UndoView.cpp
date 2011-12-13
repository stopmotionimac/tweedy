#include "UndoView.hpp"
#include <QtCore/QString>
#include <iostream>
#include <string>


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
            std::stack<IUndoRedoCommand*>& copyUndoStack = this->cmdMan->getUndoStack();
            std::stack<IUndoRedoCommand*>& copyRedoStack = this->cmdMan->getRedoStack();
            
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
    while(!pileString.empty()){
        this->addItem(pileString.top());
        pileString.pop();
    }
}



UndoWidget::UndoWidget( UndoView * undoView){
    
    dockLayout = new QVBoxLayout();
    
    addButton = new QPushButton("Ajouter");
    dltButton = new QPushButton("Retirer");
    
    this->undoView = undoView;
    
    
    undoView->fillStringStack();
    undoView->fill();
    
    dockLayout->addWidget(addButton);
    dockLayout->addWidget(dltButton);
    dockLayout->addWidget(undoView);
    
    this->setLayout(dockLayout);
    
}

UndoWidget::~UndoWidget(){
    
    delete dockLayout;
    delete addButton;
    delete dltButton;
}