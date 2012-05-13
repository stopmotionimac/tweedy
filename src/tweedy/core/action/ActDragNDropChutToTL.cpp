#include <tweedy/core/action/ActDragNDropChutToTL.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/command/clip/CmdInsertClip.hpp>

ActDragNDropChutToTL::ActDragNDropChutToTL()
        :IAction("Action Drag and Drop from Chutier to Timeline")
{

}

ActDragNDropChutToTL::~ActDragNDropChutToTL()
{

}

void ActDragNDropChutToTL::operator ()(const std::string& filename, int position)
{
    Projet& project = Projet::getInstance();
    
    //creation of the moving command of a clip to the timeline
    IUndoRedoCommand* cmd = new CmdInsertClip(filename,"Cmd Insert Clip : "+filename, position);
    
    //add the command to the command manager
    CommandManager& cmdMng = project.getCommandManager();
    cmdMng.pushNewCommand(cmd);    
}
