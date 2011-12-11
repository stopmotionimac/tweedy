#ifndef UNDOREDOCOMMAND_HPP
#define	UNDOREDOCOMMAND_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/ptr_container/ptr_vector.hpp>

class Somme{
public:
    
    Somme(int i):value(i){};
    ~Somme(){}
    
    int getSommeValue() const;
    void setSommeValue(int value);
    
private:
    int value;
};



/* ----- Interface UndoRedoCommand ----- */

class IUndoRedoCommand{
public:
    virtual ~IUndoRedoCommand(){};
    
    virtual void undo()= 0;
    virtual void redo()= 0;
    virtual void getName() const = 0;
};

/* ---------- Classe AddCommand -----------*/


class AddCommand : public IUndoRedoCommand
 {
    
 public:
     AddCommand(int i, std::string s, Somme& somme): value(i), text(s), target(somme){
         
     }
     
     ~AddCommand(){};
     
     
     virtual void undo();
     virtual void redo();
     
     virtual void getName() const;

     /*
     bool operator==(const AddCommand& o)const;
    
     bool operator==(const ICommand& o)const;
      */
     
 private:
     int value;
     std::string text;
     Somme& target ;
 };
 
 
 /* ---------- Classe DeleteCommand -----------*/

 
 class DeleteCommand : public IUndoRedoCommand
 {
    
 public:
     DeleteCommand(int i, std::string s, Somme& somme): value(i), text(s), target(somme){
         
     }
     
     ~DeleteCommand(){}
     
     
     virtual void undo();
     virtual void redo();
     
     virtual void getName() const;

     /*
     bool operator==(const DeleteCommand& o)const;
    
     bool operator==(const ICommand& o)const;
     */
 private:
     int value;
     std::string text;
     Somme& target;
 };



/* ----- CommandManager ------*/


class CommandManager
{
public:
    CommandManager(): somme(0){}
    
    ~CommandManager() {}
    
    bool isActive() const;
    void setActive(bool active = true) ;
    
    
    int getCleanIndex() const;
    
    bool canUndo() const;
    bool canRedo() const;
    
    
    int getUndoLimit() const;
    int getRedoLimit() const;
    
    
    void setUndoLimit(int limit);
    void setRedoLimit(int limit);
    
    
    //void beginMacro (const std::string&  text);
    
    void clean();
    bool isClean() const;
    
    size_t count() const;
    size_t countUndo() const;
    size_t countRedo() const;
    
    IUndoRedoCommand* getCommandToUndo();
    IUndoRedoCommand& getCommandToRedo();
    
    void pushNewCommand(IUndoRedoCommand * newCommand);
    
    void undo();        /* will be implemented as slots */
    void redo();

    Somme& getSomme();
    
    boost::ptr_vector<IUndoRedoCommand>* getUndoStack();
    boost::ptr_vector<IUndoRedoCommand>* getRedoStack();
    
    
private:
    boost::ptr_vector<IUndoRedoCommand> undoStack;
    boost::ptr_vector<IUndoRedoCommand> redoStack;
    
    bool active;
    
    int cleanIndex;
    
    int undoLimit;
    int redoLimit;
    
    Somme somme; /* pour le test , il faudra ensuite le placer dans un autre objet */
    
};



#endif	/* UNDOREDOCOMMAND_HPP */

