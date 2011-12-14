#ifndef COMMANDMANAGER_HPP
#define	COMMANDMANAGER_HPP

#include "Somme.hpp"
#include "AddCommand.hpp"
#include "DeleteCommand.hpp"

#include <cstdlib>
#include <iostream>
#include <stack>


class CommandManager
{
public:
    
    CommandManager(): somme(0),undoStack(), redoStack(){}
    
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
    IUndoRedoCommand* getCommandToRedo();
    
    void pushNewCommand(IUndoRedoCommand * newCommand);
    
    void undo();        /* will be implemented as slots */
    void redo();

    Somme& getSomme();
    
    std::stack<IUndoRedoCommand*>& getUndoStack();
    std::stack<IUndoRedoCommand*>& getRedoStack();
    
    
private:
    std::stack<IUndoRedoCommand *> undoStack;
    std::stack<IUndoRedoCommand *> redoStack;
    
    bool active;
    
    int cleanIndex;
    
    int undoLimit;
    int redoLimit;
    
    Somme somme; /* pour le test , il faudra ensuite le placer dans un autre objet */
    
};


#endif	/* COMMANDMANAGER_HPP */

