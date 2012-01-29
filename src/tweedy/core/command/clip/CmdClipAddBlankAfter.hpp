#ifndef CMDCLIPADDBLANKAFTER_HPP
#define	CMDCLIPADDBLANKAFTER_HPP

#include <tweedy/core/Clip.hpp>
#include <tweedy/core/command/IUndoRedoCommand.hpp>

class CmdClipAddBlankAfter : public IUndoRedoCommand
{
public:
        
    CmdClipAddBlankAfter(const std::string& idClip, const std::string& text);

    ~CmdClipAddBlankAfter();
    
    CmdClipAddBlankAfter* clone() const;


    void undo();
    void runDo();
    void redo();

    const std::string& getText() const;
    
    
    
    
private:
    
    std::string _text;
    std::string _idClip;
    double _value;
    bool _blankb;
    bool _blanka;
    
};


#endif	/* CMDCLIPADDBLANKAFTER_HPP */

