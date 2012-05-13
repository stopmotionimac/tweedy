#ifndef COMMANDMANAGER_HPP
#define	COMMANDMANAGER_HPP

#include <tweedy/core/command/IUndoRedoCommand.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/signal.hpp>

#include <cstdlib>
#include <iostream>
#include <stack>


class CommandManager
{
public:
    
    CommandManager(): _undoRedoVector(),_index(0){}
    
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
        
    void clean();
    bool isClean() const;
    
    size_t count() const;
    size_t countUndo() const;
    size_t countRedo() const;
    
    void pushNewCommand(IUndoRedoCommand * newCommand);
    
    void undo();        
    void redo();

    boost::ptr_vector<IUndoRedoCommand>& getUndoRedoVector();
    
    size_t getIndex();
    
    boost::signal0<void>& getSignalChanged();
    
    
private:
    
    boost::ptr_vector<IUndoRedoCommand> _undoRedoVector;
    
    boost::signal0<void> _signalChanged;
    
    size_t _index;
    
    bool _active;
    
    int _cleanIndex;
    
    int _undoLimit;
    int _redoLimit;
    
};

#endif	/* COMMANDMANAGER_HPP */
