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
            std::stack<IUndoRedoCommand*>& copyStack = this->cmdMan->getUndoStack();
            while(!copyStack.empty()){
                std::cout << (*copyStack.top()).getText() << std::endl;
                QString q;
                pileString.push(q.fromStdString((*copyStack.top()).getText()));
                copyStack.pop();
                
            }
}

void UndoView::fill(){
    while(!pileString.empty()){
        this->addItem(pileString.top());
        pileString.pop();
    }
}
/*
MainWindow::MainWindow()
 {

     createUndoView();

     setWindowTitle("Undo Framework");


 }

 void MainWindow::createUndoView()
 {
     CommandManager cmdMan ;
    
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;
    
    cmdMan.pushNewCommand(new AddCommand(2,"command +2", cmdMan.getSomme()));
    
     undoView = new UndoView(&cmdMan);
     undoView->setWindowTitle(tr("Command List"));
     undoView->show();
     undoView->setAttribute(Qt::WA_QuitOnClose, false);
 }
 */