/* 
 * File:   main.cpp
 * Author: nexus_21
 *
 * Created on 14 novembre 2011, 22:47
 */

#include <cstdlib>

#include <iostream>

using namespace std;

/*------- Interface ICommand -------*/

class ICommand{
public:

    virtual ~ICommand() = 0;
        
    virtual void execute(){
        std::cout<<" ---Execution--- "<<std::endl;
    }
};

ICommand::~ICommand() {}




/*----- Classe CommandInt ------*/

class CommandInt : public ICommand{
public:
    
    CommandInt(int i): a(i){
        
    }
 
    void execute();
    
private:
    int a;
};



void CommandInt::execute(){
    ICommand::execute();
    
    std::cout<< "  --CommandInt-- " <<std::endl;
    std::cout<< "\t" << a <<std::endl;
}




/*------ Classe CommandChar ------*/

class CommandChar : public ICommand{
public:
    
    CommandChar(char c):a(c){
        
    }
    
    void execute();

private:
    
    char a;
    
};

void CommandChar::execute(){
    ICommand::execute();
    
    std::cout<< "  --CommandChar-- " <<std::endl;
    std::cout<<"\t"<< a <<std::endl;
}



class Invoker {
public:
    
    void invoke(ICommand& cmd);
};

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