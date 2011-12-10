#ifndef UNDOREDOCOMMAND_HPP
#define	UNDOREDOCOMMAND_HPP

#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/ptr_container/ptr_vector.hpp>

class Somme{
public:
    
    Somme(int i):value(i){};
    ~Somme();
    
    int getSommeValue() const;
    void setSommeValue(int value);
    
private:
    int value;
};



/* ----- Interface UndoRedoCommand ----- */

class UndoRedoCommand{
public:
    virtual ~UndoRedoCommand() =0;
    
    virtual void undo();
    virtual void redo();
        
};

/* ---------- Classe AddCommand -----------*/


class AddCommand : public UndoRedoCommand
 {
    
 public:
     AddCommand(int i, std::string s, Somme& somme): value(i), text(s), target(somme){
         
     }
     
     ~AddCommand();
     
     
     void undo();
     void redo();

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

 
 class DeleteCommand : public UndoRedoCommand
 {
    
 public:
     DeleteCommand(int i, std::string s, Somme& somme): value(i), text(s), target(somme){
         
     }
     
     ~DeleteCommand();
     
     
     void undo();
     void redo();

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
    CommandManager(): somme(0){};
    
    ~CommandManager();
    
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
    
    UndoRedoCommand& getCommandToUndo();
    UndoRedoCommand& getCommandToRedo();
    
    void pushNewCommand(UndoRedoCommand * newCommand);
    
    void undo();        /* will be implemented as slots */
    void redo();

    Somme& getSomme();
    
    
private:
    boost::ptr_vector<UndoRedoCommand> undoStack;
    boost::ptr_vector<UndoRedoCommand> redoStack;
    
    bool active;
    
    int cleanIndex;
    
    int undoLimit;
    int redoLimit;
    
    Somme somme; /* pour le test , il faudra ensuite le placer dans un autre objet */
    
};



#endif	/* UNDOREDOCOMMAND_HPP */

