#include "AddCommand.hpp"

#include <iostream>


/*

AddCommand::AddCommand(int i, std::string s, Somme& somme): value(i), text(s), target(somme){
    std::cout << "Ctor addCommand" << std::endl;
}
*/

AddCommand::~AddCommand(){
    std::cout << "Dtor addCommand" << std::endl;
}


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


AddCommand* AddCommand::clone() const{
    return  new AddCommand(*this);
}
