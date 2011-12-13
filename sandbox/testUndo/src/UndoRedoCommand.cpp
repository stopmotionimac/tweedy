#include "UndoRedoCommand.hpp"

#include <cstdlib>
#include <iostream>
#include <boost/ptr_container/ptr_vector.hpp>
#include <string>



int Somme::getSommeValue() const{
    return value;
}

void Somme::setSommeValue(int newValue){
    value = newValue;
}

/* ---- Interface UndoRedoCommand ----*/

//IUndoRedoCommand::~IUndoRedoCommand() {}



/* ------ AddCommand ------ */


void AddCommand::undo(){
    target.setSommeValue(target.getSommeValue()-value);
}

void AddCommand::runDo(){
    target.setSommeValue(target.getSommeValue()+value);
}

void AddCommand::redo(){
    this->runDo();
}

void AddCommand::getName() const{
    std::cout<<text<<std::endl;
}

void AddCommand::setText(const std::string & newText){
    text = newText;
}

std::string AddCommand::getText(){
    return text;
}

/* ------ DeleteCommand ------ */


void DeleteCommand::undo(){
    target.setSommeValue(target.getSommeValue()+value);
}

void DeleteCommand::runDo(){
    target.setSommeValue(target.getSommeValue()-value);
}

void DeleteCommand::redo(){
    this->runDo();
}

void DeleteCommand::getName() const{
    std::cout<<text<<std::endl;
}

void DeleteCommand::setText(const std::string & newText){
    text = newText;
}

std::string DeleteCommand::getText(){
    return text;
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
    while(!this->getUndoStack().empty())
        this->getUndoStack().pop();
    while(!this->getRedoStack().empty())
        this->getRedoStack().pop();
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





IUndoRedoCommand* CommandManager::getCommandToUndo(){
    IUndoRedoCommand* cmd = this->getUndoStack().top();
    this->getUndoStack().pop();
    return cmd;
}

IUndoRedoCommand* CommandManager::getCommandToRedo(){
    IUndoRedoCommand* cmd = this->getRedoStack().top();
    this->getRedoStack().pop();
    return cmd;
}



void CommandManager::pushNewCommand(IUndoRedoCommand* newCommand){
    
    /* pusher the new command into the undoStack and execute it*/
    this->getUndoStack().push(newCommand);
    newCommand->runDo();         //will be modified
}


void CommandManager::undo(){
    
    if (this->canUndo()){
        IUndoRedoCommand* cmd = this->getCommandToUndo();
        cmd->getName();
        cmd->undo();
        this->getRedoStack().push(cmd);
    }
    else
        std::cout << "No command to undo" << std::endl; /* case of no command to undo will be implement
                                                      * with the slot */
}


void CommandManager::redo(){
    
    if (this->canRedo()){
        IUndoRedoCommand* cmd = this->getCommandToRedo();
        cmd->getName();
        cmd->redo();
        this->getUndoStack().push(cmd);
    }
    else
        std::cout << "No command to redo" << std::endl; /* case of no command to undo will be implement
                                                      * with the slot */
}


Somme& CommandManager::getSomme(){
    return somme;
}

/*renvoyer un const ptr vers les stacks ?*/

 std::stack<IUndoRedoCommand *>& CommandManager::getUndoStack(){   
     return this->undoStack;
 }
 
 std::stack<IUndoRedoCommand*>& CommandManager::getRedoStack(){
     return this->redoStack;
 }
