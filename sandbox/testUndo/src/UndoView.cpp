#include "UndoView.hpp"
#include <QtCore/QString>



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
    this->emptyLabel.operator =(label) ;
}
        
QUndoGroup * UndoView::group() const{
    return this->undoGroup;
}
        
boost::ptr_vector<IUndoRedoCommand>* UndoView::stack() const{
    return this->cmdMan->getUndoStack();
}

