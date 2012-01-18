#ifndef COMMANDMANAGER_HPP
#define	COMMANDMANAGER_HPP

#include "../../../tests/tweedy/undo/Somme.hpp"
#include "../../../tests/tweedy/undo/AddCommand.hpp"
#include "../../../tests/tweedy/undo/DeleteCommand.hpp"

#include <tweedy/core/IUndoRedoCommand.hpp>

#include <boost/ptr_container/ptr_vector.hpp>

#include <cstdlib>
#include <iostream>
#include <stack>


class CommandManager
{
public:
    
    CommandManager(): somme(0),m_undoRedoVector(){}
    
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
    
    size_t getCommandToUndo();
    size_t getCommandToRedo();
    
    void pushNewCommand(IUndoRedoCommand * newCommand);
    
    void undo();        /* will be implemented as slots */
    void redo();

    Somme& getSomme();
    
    ///#### useless
    std::stack<IUndoRedoCommand*>& getUndoStack();
    std::stack<IUndoRedoCommand*>& getRedoStack();
    ///####
    
    boost::ptr_vector<IUndoRedoCommand> getUndoRedoVector();
    
    size_t getIndex();
    
    
private:
    std::stack<IUndoRedoCommand *> undoStack;
    std::stack<IUndoRedoCommand *> redoStack;
    
    boost::ptr_vector<IUndoRedoCommand> m_undoRedoVector;
    
    size_t m_index;
    
    bool active;
    
    int cleanIndex;
    
    int undoLimit;
    int redoLimit;
    
    Somme somme; /* pour le test , il faudra ensuite le placer dans un autre objet */
    
};


#endif	/* COMMANDMANAGER_HPP */

