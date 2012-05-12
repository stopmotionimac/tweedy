#include <tweedy/core/action/ActDragNDropTLToTL.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/command/clip/CmdMoveClip.hpp>

ActDragNDropTLToTL::ActDragNDropTLToTL()
        :IAction("Action Drag and Drop from Timeline to Timeline")
{
    
}

ActDragNDropTLToTL::~ActDragNDropTLToTL()
{
    
}

void ActDragNDropTLToTL::operator ()(const std::string& idClip, int position)
{
    Projet& project = Projet::getInstance();
    
    //creation of a command for moving a clip in the timeline
    IUndoRedoCommand* cmd = new CmdMoveClip(idClip,"Cmd Move Clip : "+idClip, position);
    
    //add the command to the command manager
    CommandManager& cmdMng = project.getCommandManager();
    cmdMng.pushNewCommand(cmd);
}
