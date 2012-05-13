#include <tweedy/core/CommandManager.hpp>
#include <tweedy/core/command/IUndoRedoCommand.hpp>

bool CommandManager::isActive() const{
    return _active;
}

void CommandManager::setActive(bool active){
    active = active;
}

int CommandManager::getCleanIndex() const{
    return _cleanIndex;
}

int CommandManager::getUndoLimit() const{
    return _undoLimit;
}

int CommandManager::getRedoLimit() const{
    return _redoLimit;
}

void CommandManager::setUndoLimit(int limit){
    _undoLimit = limit;
}

void CommandManager::setRedoLimit(int limit){
    _redoLimit = limit;
}

//if indice of the current command is > 0
bool CommandManager::canUndo() const{
    return _index!=0;
}

bool CommandManager::canRedo() const{
    return _index!= _undoRedoVector.size();
}

void CommandManager::clean(){
    _undoRedoVector.clear();
    _index = 0;
}

bool CommandManager::isClean() const{           /* a verifier */
    return (_undoRedoVector.empty());
}

size_t CommandManager::countUndo() const{
    return _index;
}

size_t CommandManager::countRedo() const{
    return (_undoRedoVector.size() - _index);
}

size_t CommandManager::count() const{
    return _undoRedoVector.size();
}

void CommandManager::pushNewCommand(IUndoRedoCommand* newCommand){
    /* clear the redo part of undoRedoVector*/
    _undoRedoVector.erase( _undoRedoVector.begin()+_index, _undoRedoVector.end() );
            
    /* push the new command into the undo part and execute it*/
    _undoRedoVector.push_back(newCommand);
    
    newCommand->runDo();
    ++_index;
    _signalChanged();
}

void CommandManager::undo(){
    if (this->canUndo()){
        size_t indexUndoCommand = --_index;
        _undoRedoVector[indexUndoCommand].undo();
        _signalChanged();
    }
}

void CommandManager::redo(){
    if( !this->canRedo() )
    {
        return;
    }
    size_t indexUndoCommand = _index++;
    _undoRedoVector[indexUndoCommand].redo();
    _signalChanged();
}

 boost::ptr_vector<IUndoRedoCommand>& CommandManager::getUndoRedoVector(){
     return _undoRedoVector;
 }
 
 size_t CommandManager::getIndex(){
     return _index;
 }
 
 boost::signal0<void>& CommandManager::getSignalChanged(){
     return _signalChanged;
 }
