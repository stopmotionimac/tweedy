#ifndef IUNDOREDOCOMMAND_HPP
#define	IUNDOREDOCOMMAND_HPP

#include <string>

class IUndoRedoCommand{
public:
    virtual ~IUndoRedoCommand(){};
    
    virtual void undo()= 0;
    virtual void runDo()=0;
    virtual void redo()= 0;
    virtual void getName() const = 0;
    virtual void setText(const std::string &text)=0;
    virtual std::string getText() =0;
};



#endif	/* IUNDOREDOCOMMAND_HPP */

