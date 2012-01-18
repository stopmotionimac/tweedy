#include "CommandManager.hpp"
#include "IUndoRedoCommand.hpp"

bool CommandManager::isActive() const{
    return active;
}

void CommandManager::setActive(bool active){
    active = active;
}






int CommandManager::getCleanIndex() const{
    return cleanIndex;
}





int CommandManager::getUndoLimit() const{
    return undoLimit;
}

int CommandManager::getRedoLimit() const{
    return redoLimit;
}

void CommandManager::setUndoLimit(int limit){
    undoLimit = limit;
}

void CommandManager::setRedoLimit(int limit){
    redoLimit = limit;
}





//si l'indice de la commande courante est superieur à 0
bool CommandManager::canUndo() const{
    return m_index!=0;
}


bool CommandManager::canRedo() const{
    return m_index!= m_undoRedoVector.size();
}






void CommandManager::clean(){
    m_undoRedoVector.clear();
    m_index = 0;
}

bool CommandManager::isClean() const{           /* a verifier */
    return (m_undoRedoVector.empty());
}




size_t CommandManager::countUndo() const{
    return m_index;
}

size_t CommandManager::countRedo() const{
    return (m_undoRedoVector.size() - m_index);
}


size_t CommandManager::count() const{
    return m_undoRedoVector.size();
}





size_t CommandManager::getCommandToUndo(){
    
    --m_index;
    
    return m_index;
}

size_t CommandManager::getCommandToRedo(){
    
    ++m_index;
    
    return m_index;
}



void CommandManager::pushNewCommand(IUndoRedoCommand* newCommand){
        
    /* clear the redo part of undoRedoVector*/
    for(unsigned int i = m_index; i<m_undoRedoVector.size() ; ++i){
        m_undoRedoVector.pop_back();
    }
    
    /* push the new command into the undo part and execute it*/
    m_undoRedoVector.push_back(newCommand);
    newCommand->runDo();
    
}


void CommandManager::undo(){
    
    if (this->canUndo()){
        size_t indexUndoCommand = this->getCommandToUndo();
        m_undoRedoVector[indexUndoCommand].getName();
        m_undoRedoVector[indexUndoCommand].undo();
    }
    else
        std::cout << "No command to undo" << std::endl; /* case of no command to undo will be implement
                                                      * with the slot */
}


void CommandManager::redo(){
    
    if (this->canRedo()){
        size_t indexUndoCommand = this->getCommandToRedo();
        m_undoRedoVector[indexUndoCommand].getName();
        m_undoRedoVector[indexUndoCommand].redo();
    }
    else
        std::cout << "No command to redo" << std::endl; /* case of no command to undo will be implement
                                                      * with the slot */
}


/*renvoyer un const ptr vers les stacks ?*/

 std::stack<IUndoRedoCommand *>& CommandManager::getUndoStack(){   
     return this->undoStack;
 }
 
 std::stack<IUndoRedoCommand*>& CommandManager::getRedoStack(){
     return this->redoStack;
 }


 boost::ptr_vector<IUndoRedoCommand> CommandManager::getUndoRedoVector(){
     return m_undoRedoVector;
 }
 
 size_t CommandManager::getIndex(){
     return m_index;
 }