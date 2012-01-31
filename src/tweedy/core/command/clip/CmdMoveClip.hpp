#ifndef CMDMOVECLIP_HPP
#define	CMDMOVECLIP_HPP


#include <tweedy/core/command/IUndoRedoCommand.hpp>

class CmdMoveClip : public IUndoRedoCommand
{
    
public:
    
    CmdMoveClip(const std::string& idClip, const std::string& text,int newPosition);

    ~CmdMoveClip();
    
    CmdMoveClip* clone() const;


    void undo();
    void runDo();
    void redo();

    const std::string& getText() const;
    
    
    
private:
    
    std::string _text;
    std::string _idClip;
    int _newPosition;
    int _oldPosition;
    
};

#endif	/* CMDMOVECLIP_HPP */

