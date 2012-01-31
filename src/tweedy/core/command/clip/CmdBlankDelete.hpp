#ifndef CMDBLANKDELETE_HPP
#define	CMDBLANKDELETE_HPP

#include <tweedy/core/command/IUndoRedoCommand.hpp>

class CmdBlankDelete : public IUndoRedoCommand
{

public:

    CmdBlankDelete(int currentTime, const std::string& text);
    
    ~CmdBlankDelete();
    
    CmdBlankDelete* clone() const;


    void undo();
    void runDo();
    void redo();

    const std::string& getText() const;
    
private:
    
    int _currentTime;
    std::string _text;
    
};

#endif	/* CMDBLANKDELETE_HPP */

