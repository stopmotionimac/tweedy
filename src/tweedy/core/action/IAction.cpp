#include "IAction.hpp"

IAction::IAction(const std::string& name):_name(name){
    
}

IAction::~IAction(){}


std::string IAction::getName() const{
    return _name;
}
