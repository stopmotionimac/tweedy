#include <tweedy/core/UndoRedoCommand.hpp>

#include <cstdlib>
#include <iostream>



int Somme::getSommeValue() const{
    return value;
}

void Somme::setSommeValue(int newValue){
    value = newValue;
}

/* ---- Interface UndoRedoCommand ----*/

IUndoRedoCommand::~IUndoRedoCommand() {}



/* ------ AddCommand ------ */


void AddCommand::undo(){
    target.setSommeValue(target.getSommeValue()-value);
}

void AddCommand::redo(){
    target.setSommeValue(target.getSommeValue()+value);
}

/* ------ DeleteCommand ------ */


void DeleteCommand::undo(){
    target.setSommeValue(target.getSommeValue()+value);
}

void DeleteCommand::redo(){
    target.setSommeValue(target.getSommeValue()-value);
}


/* ##############    CommandManager   ############ */



/* Getters and setters */

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






bool CommandManager::canUndo() const{
    return !undoStack.empty();
}


bool CommandManager::canRedo() const{
    return !redoStack.empty();
}






void CommandManager::clean(){
    undoStack.clear();
    redoStack.clear();
}

bool CommandManager::isClean() const{           /* a verifier */
    return (undoStack.empty() && redoStack.empty());
}




size_t CommandManager::countUndo() const{
    return undoStack.size();
}

size_t CommandManager::countRedo() const{
    return redoStack.size();
}


size_t CommandManager::count() const{
    return countUndo() + countRedo();
}





IUndoRedoCommand& CommandManager::getCommandToUndo(){
    
    IUndoRedoCommand& cmd = undoStack.back();
    undoStack.pop_back();
    return cmd;
}

IUndoRedoCommand& CommandManager::getCommandToRedo(){
    IUndoRedoCommand& cmd = redoStack.back();
    redoStack.pop_back();
    return cmd;
}





void CommandManager::pushNewCommand(IUndoRedoCommand* newCommand){
    
    /* pusher the new command into the undoStack and execute it*/
    undoStack.push_back(newCommand);
    newCommand->redo();         //will be modified
}


void CommandManager::undo(){
    
    if (this->canUndo()){
        IUndoRedoCommand& cmd = this->getCommandToUndo();
        cmd.undo();
        redoStack.push_back(&cmd);
    }
    else
        std::cout << "No command to undo" << std::endl; /* case of no command to undo will be implement
                                                      * with the slot */
}


void CommandManager::redo(){
    
    if (this->canRedo()){
        IUndoRedoCommand& cmd = this->getCommandToRedo();
        cmd.redo();
        undoStack.push_back(&cmd);
    }
    else
        std::cout << "No command to redo" << std::endl; /* case of no command to undo will be implement
                                                      * with the slot */
}


Somme& CommandManager::getSomme(){
    return somme;
}

