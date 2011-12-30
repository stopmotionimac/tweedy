#include "DeleteCommand.hpp"

#include <iostream>


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

