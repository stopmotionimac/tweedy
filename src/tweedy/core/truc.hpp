#include <cstdlib>

#include <iostream>



/*------- Interface ICommand -------*/

class ICommand{
public:

    virtual ~ICommand() = 0;
        
    virtual void execute()
    {
        std::cout<<" ---Execution--- "<<std::endl;
       
    }
    
    virtual std::ostream& cout( std::ostream& o ) const
    {
        o << "ICommand" << std::endl;
        return o;
    }
    virtual bool operator==(const ICommand&)const=0;
};

std::ostream& operator<<( std::ostream& o, const ICommand& command );

/*----- Classe CommandInt ------*/

class CommandInt : public ICommand{
public:
    
    CommandInt(int i): a(i){
        
    }
 
    void execute();
    
    bool operator==(const CommandInt& o)const;
    
    bool operator==(const ICommand& o)const;
    
private:
    int a;
};



/*------ Classe CommandChar ------*/

class CommandChar : public ICommand{
public:
    
    CommandChar(char c):a(c){
        
    }
    
    void execute();
    
    
    bool operator==(const CommandChar& o)const;
    
    bool operator==(const ICommand& o)const;

private:
    
    char a;
    
};


/* ---- Invocateur ----*/

class Invoker {
public:
    
    void invoke(ICommand& cmd);
};

