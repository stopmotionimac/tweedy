#ifndef CMDINSERTCLIP_HPP
#define	CMDINSERTCLIP_HPP

#include <tweedy/core/command/IUndoRedoCommand.hpp>
#include <tweedy/core/Clip.hpp>

class CmdInsertClip : public IUndoRedoCommand
{
    
public:
    
    CmdInsertClip(const std::string& filename, const std::string& text,int newPosition);

    ~CmdInsertClip();
    
    CmdInsertClip* clone() const;


    void undo();
    void runDo();
    void redo();

    const std::string& getText() const;
    
    
    
private:
    
    std::string _text;
    std::string _filename;
    int _newPosition;
    Clip _clipTemp;
    
};

#endif	/* CMDINSERTCLIP_HPP */

