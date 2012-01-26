#include <tweedy/gui/Undo/UndoView.hpp>
#include "tweedy/core/command/GroupeUndoRedoCmd.hpp"
#include <QtCore/QString>
#include <iostream>
#include <string>
#include <QtCore/QVariant>
#include <boost/foreach.hpp>


struct UndoViewUpdater
{
    UndoViewUpdater(UndoView& undoView):m_undoView(undoView)
    {

    }
    
    void operator()()
    {
        m_undoView.fill();
    }
    
    UndoView& m_undoView;
};



UndoView::UndoView(CommandManager& cmdManager, QWidget * parent)
        : QListWidget(parent), _cmdMan(cmdManager)
{
    //connecter l'update de l'UndoView au signalChanged du commandManager
    UndoViewUpdater upd(*this);

    _cmdMan.getSignalChanged().connect(upd);

}


UndoView::~UndoView()
{
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
    
    BOOST_FOREACH( const IUndoRedoCommand& command, _cmdMan.getUndoRedoVector() )
    {
            
        ///on recupere le texte de la commande courante que l'on convertit en QString
        const std::string& undoRedoComment = command.getText();

        ///on ajoute cette QString comme item de la UndoView
        this->addItem( QString::fromStdString(undoRedoComment) );
    }

    
    ///l'item courant est la derniere commande executee
    this->setCurrentItem(this->item(_cmdMan.getIndex()-1));
    
}

CommandManager& UndoView::getCmdMan(){
    return _cmdMan;
}
