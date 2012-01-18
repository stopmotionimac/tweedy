#include "UndoView.hpp"
#include <QtCore/QString>
#include <iostream>
#include <string>
#include <QtCore/QVariant>
#include <boost/foreach.hpp>


UndoView::~UndoView(){
    delete this->p_cmdMan;
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

void UndoView::fill(){
    //on vide la pile
    this->clear();

    
    BOOST_FOREACH( const IUndoRedoCommand& command, p_cmdMan->getUndoRedoVector() )
    {
        ///on recupere le texte de la commande courante que l'on convertit en QString
        const std::string& undoRedoComment = command.getText();
        
        std::cout << undoRedoComment << std::endl;

        ///on ajoute cette QString comme item de la UndoView
        this->addItem( QString::fromStdString(undoRedoComment) );
    }

    
    ///l'item courant est la derniere commande executee
    this->setCurrentItem(this->item(p_cmdMan->getIndex()-1));
    
}

CommandManager* UndoView::getCmdMan(){
    return p_cmdMan;
}


/*
void UndoView::fill1(){
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

*/

/*
std::stack<IUndoRedoCommand *>& UndoView::stack() const{
    return this->cmdMan->getUndoStack();
}


void UndoView::fillStringUndoStack(){
            std::stack<IUndoRedoCommand*> copyUndoStack(this->cmdMan->getUndoStack());
            
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
*/