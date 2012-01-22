#include <tweedy/core/CommandManager.hpp>
#include <tweedy/core/command/IUndoRedoCommand.hpp>

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



void CommandManager::pushNewCommand(IUndoRedoCommand* newCommand){
    
        
    /* clear the redo part of undoRedoVector*/
    m_undoRedoVector.erase( m_undoRedoVector.begin()+m_index, m_undoRedoVector.end() );
            
    /* push the new command into the undo part and execute it*/
    m_undoRedoVector.push_back(newCommand);
    newCommand->runDo();
    ++m_index;
}


void CommandManager::undo(){
    
    if (this->canUndo()){
        size_t indexUndoCommand = --m_index;
        m_undoRedoVector[indexUndoCommand].getName();
        m_undoRedoVector[indexUndoCommand].undo();
    }
    else
        std::cout << "No command to undo" << std::endl; /* case of no command to undo will be implement
                                                      * with the slot */
}


void CommandManager::redo(){
    
    if (this->canRedo()){
        size_t indexUndoCommand = m_index++;
        m_undoRedoVector[indexUndoCommand].getName();
        m_undoRedoVector[indexUndoCommand].redo();

    }
    else
        std::cout << "No command to redo" << std::endl; /* case of no command to undo will be implement
                                                      * with the slot */
}

 boost::ptr_vector<IUndoRedoCommand> CommandManager::getUndoRedoVector(){
     return m_undoRedoVector;
 }
 
 size_t CommandManager::getIndex(){
     return m_index;
 }