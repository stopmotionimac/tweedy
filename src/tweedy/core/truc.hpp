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
    
    virtual bool operator==(const ICommand&)=0;
};



/*----- Classe CommandInt ------*/

class CommandInt : public ICommand{
public:
    
    CommandInt(int i): a(i){
        
    }
 
    void execute();
    
    bool operator==(const CommandInt& o);
    
    bool operator==(const ICommand& o);
    
private:
    int a;
};



/*------ Classe CommandChar ------*/

class CommandChar : public ICommand{
public:
    
    CommandChar(char c):a(c){
        
    }
    
    void execute();
    
    
    bool operator==(const CommandChar& o);
    
    bool operator==(const ICommand& o);

private:
    
    char a;
    
};


/* ---- Invocateur ----*/

class Invoker {
public:
    
    void invoke(ICommand& cmd);
};

