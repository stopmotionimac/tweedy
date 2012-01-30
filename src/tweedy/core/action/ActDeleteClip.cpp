#include <tweedy/core/action/ActDeleteClip.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/CommandManager.hpp>
#include <tweedy/core/command/clip/CmdClipDelete.hpp>
#include <tweedy/core/command/clip/CmdBlankDelete.hpp>

ActDeleteClip::ActDeleteClip()
        :IAction("Action Delete Clip")
{
    
}

void ActDeleteClip::operator()(int currentTime)
{

    
    //récupérer le clip à traiter
    std::string filename = "img/none.jpg";
    
    Projet& projet = Projet::getInstance();
    
    Timeline timeline = projet.getTimeline();

    bool isClip = timeline.findCurrentClip(filename,currentTime);
    
    if(!isClip)
    {
        
        std::cout<< "Clip not found" << std::endl;
        //creation d'une commande de suppression de blanc
        IUndoRedoCommand* cmd = new CmdBlankDelete(currentTime, "Command Blank Delete");
        
        //ajout de la commande au commande manager
        CommandManager& cmdMng = projet.getCommandManager();
        cmdMng.pushNewCommand(cmd);
    }
    
    else
    {
        //creation d'une commande de suppression de clip
        IUndoRedoCommand* cmd = new CmdClipDelete(filename, "Command Clip " +filename +" Delete");
        
        //ajout de la commande au commande manager
        CommandManager& cmdMng = projet.getCommandManager();
        cmdMng.pushNewCommand(cmd);
    }
    
    
    
    //fin de l'action
    std::cout << "Action done" << std::endl;
}

ActDeleteClip::~ActDeleteClip()
{
        std::cout << "Dtor action : " +_name << std::endl;

}

