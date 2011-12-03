#include "icommand.hpp"

#include <cstdlib>
#include <iostream>


std::ostream& operator<<( std::ostream& o, const ICommand& command )
{
    return command.cout(o);
}

/* ---- Interface ICommand ----*/

ICommand::~ICommand() {}


/*----- Classe CommandInt ------*/


void CommandInt::execute(){
    ICommand::execute();
    
    std::cout<< "  --CommandInt-- " <<std::endl;
    std::cout<< "\t" << a <<std::endl;
}


bool CommandInt::operator==(const CommandInt& o) const{
        if(a != o.a){
            return false;
        }
        return true;
    }
    
bool CommandInt::operator==(const ICommand& o) const{
        const CommandInt* other = dynamic_cast<const CommandInt*>(&o);
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



bool CommandChar::operator==(const CommandChar& o) const{
        if(a != o.a){
            return false;
        }
        return true;
}
    
bool CommandChar::operator==(const ICommand& o) const{
        const CommandChar* other = dynamic_cast<const CommandChar*>(&o);
        if(other == NULL)
        {
            return false;
        }
        return operator==(*other);
}


/* ---- Invocateur ----*/


void Invoker::invoke(ICommand& cmd){
    std::cout << "----Invocation----" << std::endl;
    cmd.execute();
}


