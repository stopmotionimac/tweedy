#ifndef GROUPEUNDOREDOCMD_HPP
#define	GROUPEUNDOREDOCMD_HPP

#include <boost/ptr_container/ptr_vector.hpp>
#include <tweedy/core/command/IUndoRedoCommand.hpp>


class GroupeUndoRedoCmd : public IUndoRedoCommand
{
 
public:

    GroupeUndoRedoCmd(boost::ptr_vector<IUndoRedoCommand>& listeCmd,const std::string& text);

    ~GroupeUndoRedoCmd();

    GroupeUndoRedoCmd* clone() const;


    void undo();
    void runDo();
    void redo();

    void getName() const;
    void setText(const std::string &text);
    const std::string& getText() const;
    
    boost::ptr_vector<IUndoRedoCommand>& getListeCmd();
    
    //void setCmd(IUndoRedoCommand& i);
    
    
    
    
private:
    
    boost::ptr_vector<IUndoRedoCommand> _listeCmd;
    std::string _text;

    
};

#endif	/* GROUPEUNDOREDOCMD_HPP */

