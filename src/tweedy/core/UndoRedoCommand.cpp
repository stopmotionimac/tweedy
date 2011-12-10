#include "UndoRedoCommand.hpp"

#include <cstdlib>
#include <iostream>



int Somme::getSommeValue() const{
    return value;
}

void Somme::setSommeValue(int newValue){
    value = newValue;
}

/* ---- Interface UndoRedoCommand ----*/

UndoRedoCommand::~UndoRedoCommand() {}



/* ------ AddCommand ------ */


void AddCommand::undo(int somme){
    somme-=value;
}

void AddCommand::redo(int somme){
    somme+=value;
}

/* ------ DeleteCommand ------ */


void DeleteCommand::undo(int somme){
    somme +=value;
}

void DeleteCommand::redo(int somme){
    somme-=value;
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


void CommandManager::pushNewCommand(UndoRedoCommand* newCommand){
    
    /* pusher the new command into the undoStack and execute it*/
    undoStack.push_back(newCommand);
    newCommand->redo(somme);         //will be modified
}

