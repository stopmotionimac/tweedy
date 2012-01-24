#ifndef CMDCLIPADDBLANKBEFORE_HPP
#define	CMDCLIPADDBLANKBEFORE_HPP


#include <tweedy/core/Clip.hpp>
#include <tweedy/core/command/IUndoRedoCommand.hpp>

class CmdClipAddBlankBefore : public IUndoRedoCommand
{
public:
        
    CmdClipAddBlankBefore(const std::string& idClip, const std::string& text,
            double value,bool blankb = false, bool blanka = false);

    ~CmdClipAddBlankBefore();
    
    CmdClipAddBlankBefore* clone() const;


    void undo();
    void runDo();
    void redo();

    void getName() const;
    void setText(const std::string &text);
    const std::string& getText() const;
    
    
    
    
private:
    
    std::string _text;
    std::string _idClip;
    double _value;
    bool _blankb;
    bool _blanka;
    
};


#endif	/* CMDCLIPADDBLANKBEFORE_HPP */

