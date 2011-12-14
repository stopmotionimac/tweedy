#include "AddCommand.hpp"

#include <iostream>

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