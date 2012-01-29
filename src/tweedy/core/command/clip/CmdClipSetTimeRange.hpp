#ifndef CMDCLIPSETTIMERANGE_HPP
#define	CMDCLIPSETTIMERANGE_HPP

#include <tweedy/core/Clip.hpp>
#include <tweedy/core/command/IUndoRedoCommand.hpp>

class CmdClipSetTimeRange : public IUndoRedoCommand
{
public:
        
    CmdClipSetTimeRange(const std::string& idClip, const std::string& text,double value);

    ~CmdClipSetTimeRange();
    
    CmdClipSetTimeRange* clone() const;


    void undo();
    void runDo();
    void redo();

    const std::string& getText() const;
    
    
    
    
private:
    
    std::string _text;
    std::string _idClip;
    double _value;
    
};


#endif	/* CMDCLIPSETTIMERANGE_HPP */

