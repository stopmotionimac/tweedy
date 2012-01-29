#ifndef CMDCLIPDELETE_HPP
#define	CMDCLIPDELETE_HPP

#include <tweedy/core/Clip.hpp>
#include <tweedy/core/command/IUndoRedoCommand.hpp>

class CmdClipDelete : public IUndoRedoCommand
{
 
public:
        
    CmdClipDelete(const std::string& idClip, const std::string& text);
    
    ~CmdClipDelete();
    
    CmdClipDelete* clone() const;


    void undo();
    void runDo();
    void redo();

    const std::string& getText() const;
    
private:
    
    std::string _idClip;
    std::string _text;
    Clip* _clipTemp;
};

#endif	/* CMDCLIPDELETE_HPP */

