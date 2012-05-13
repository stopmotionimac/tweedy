#include <tweedy/core/action/ActDeleteClip.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/CommandManager.hpp>
#include <tweedy/core/command/clip/CmdClipDelete.hpp>


ActDeleteClip::ActDeleteClip()
        :IAction("Action Delete Clip")
{

}

ActDeleteClip::~ActDeleteClip()
{

}


void ActDeleteClip::operator()(Clip clip)
{
    Projet& projet = Projet::getInstance();

    std::string idClip = clip.getId().getIdStringForm();
    if ( idClip.find("flux") == std::string::npos)
    {
        //creation of a command to suppr clip
        IUndoRedoCommand* cmd = new CmdClipDelete(idClip, "Command Clip " +idClip +" Delete");

        //add the command to the command manager
        CommandManager& cmdMng = projet.getCommandManager();
        cmdMng.pushNewCommand(cmd);
    }
}
