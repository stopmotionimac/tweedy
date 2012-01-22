#include <tweedy/core/command/GroupeUndoRedoCmd.hpp>
#include <boost/foreach.hpp>
#include <iostream>

GroupeUndoRedoCmd::GroupeUndoRedoCmd(boost::ptr_vector<IUndoRedoCommand>& listeCmd,const std::string& text)
        :_listeCmd(listeCmd),_text(text)
{
    
}

GroupeUndoRedoCmd::~GroupeUndoRedoCmd(){
    
}

GroupeUndoRedoCmd* GroupeUndoRedoCmd::clone() const{
    return  new GroupeUndoRedoCmd(*this);
}

void GroupeUndoRedoCmd::runDo(){
    
    BOOST_FOREACH(IUndoRedoCommand& command, _listeCmd )
    {
        command.runDo();
    }
}

void GroupeUndoRedoCmd::redo(){
    
    BOOST_FOREACH(IUndoRedoCommand& command, _listeCmd )
    {
        command.redo();
    }
}

void GroupeUndoRedoCmd::undo(){
    
    BOOST_FOREACH(IUndoRedoCommand& command, _listeCmd )
    {
        command.undo();
    }
}


void GroupeUndoRedoCmd::getName() const{
    std::cout<<_text<<std::endl;
}

void GroupeUndoRedoCmd::setText(const std::string & newText){
    _text = newText;
}

const std::string& GroupeUndoRedoCmd::getText() const {
    return _text;
}

boost::ptr_vector<IUndoRedoCommand>& GroupeUndoRedoCmd::getListeCmd(){
    return _listeCmd;
}

/*
void GroupeUndoRedoCmd::setCmd(IUndoRedoCommand& i){
    _listeCmd.push_back(i);
}
*/