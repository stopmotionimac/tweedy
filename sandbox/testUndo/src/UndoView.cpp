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


void UndoView::fillStringUndoStack(){
            std::stack<IUndoRedoCommand*> copyUndoStack(this->cmdMan->getUndoStack());
            std::stack<IUndoRedoCommand*> copyRedoStack(this->cmdMan->getRedoStack());
            
            while(!copyUndoStack.empty()){
                std::cout << (*copyUndoStack.top()).getText() << std::endl;
                QString q;
                pileString.push(q.fromStdString((*copyUndoStack.top()).getText()));
                copyUndoStack.pop();
                
            }
}

void UndoView::fillStringRedoStack(){
            std::stack<IUndoRedoCommand*> copyRedoStack(this->cmdMan->getRedoStack());
            
            while(!copyRedoStack.empty()){
                std::cout << (*copyRedoStack.top()).getText() << std::endl;
                QString q;
                pileString.push(q.fromStdString((*copyRedoStack.top()).getText()));
                copyRedoStack.pop();
                
            }
}



void UndoView::fill(){
    this->clear();
    this->fillStringUndoStack();
    
    while(!pileString.empty()){
        this->addItem(pileString.top());
        pileString.pop();
    }
    
    std::cout << this->count() << std::endl;
    
    this->setCurrentItem(this->item(this->count()-1));
    
    this->fillStringRedoStack();
    
    while(!pileString.empty()){
        this->addItem(pileString.top());
        pileString.pop();
    }
}


CommandManager* UndoView::getCmdMan(){
    return cmdMan;
}
