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
        std::cout << "Dtor action : " +_name << std::endl;

}


void ActDeleteClip::operator()(Clip clip)
{

    Projet& projet = Projet::getInstance();

    std::string idClip = clip.getId().getIdStringForm();
    if ( idClip.find("flux") == std::string::npos)
    {
        //creation d'une commande de suppression de clip
        IUndoRedoCommand* cmd = new CmdClipDelete(idClip, "Command Clip " +idClip +" Delete");

        //ajout de la commande au commande manager
        CommandManager& cmdMng = projet.getCommandManager();
        cmdMng.pushNewCommand(cmd);
    }

    std::cout << "Action done" << std::endl;

}

