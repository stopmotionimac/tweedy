#include "truc.hpp"

#include <cstdlib>
#include <iostream>


/* ---- Interface ICommand ----*/

ICommand::~ICommand() {}


/*----- Classe CommandInt ------*/


void CommandInt::execute(){
    ICommand::execute();
    
    std::cout<< "  --CommandInt-- " <<std::endl;
    std::cout<< "\t" << a <<std::endl;
}


bool CommandInt::operator==(const CommandInt& o){
        if(a != o.a){
            return false;
        }
        return true;
    }
    
bool CommandInt::operator==(const ICommand& o){
        const CommandInt* other = dynamic_cast<const CommandInt*>(o);
        if(other == NULL)
        {
            return false;
        }
    return operator==(*other);
}


/*------ Classe CommandChar ------*/

void CommandChar::execute(){
    ICommand::execute();
    
    std::cout<< "  --CommandChar-- " <<std::endl;
    std::cout<<"\t"<< a <<std::endl;
}



bool CommandChar::operator==(const CommandChar& o){
        if(a != o.a){
            return false;
        }
        return true;
}
    
bool CommandChar::operator==(const ICommand& o){
        const CommandInt* other = dynamic_cast<const CommandChar*>(o);
        if(other == NULL)
        {
            return false;
        }
        return operator==(*other);
}


/* ---- Invocateur ----*/


void Invoker::invoke(ICommand& cmd){
    cout << "----Invocation----" << endl;
    cmd.execute();
}






int main(int argc, char** argv) {
    
    CommandInt command1(1);
    CommandChar command2('o');
    
    Invoker inv;
    
    inv.invoke(command1);
    inv.invoke(command2);
    
    
}