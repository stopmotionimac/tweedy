#include <tweedy/core/action/ActAddBlankAfterClip.hpp>

#include <tweedy/core/command/clip/CmdClipAddBlankAfter.hpp>
#include <tweedy/core/Projet.hpp>

#include <string>
#include <iostream>
#include <sstream>

ActAddBlankAfterClip::ActAddBlankAfterClip()
        :IAction("Action add blank after clip")
{
    
}



ActAddBlankAfterClip::~ActAddBlankAfterClip()
{
    std::cout << "Dtor action : "+_name << std::endl;
}



void ActAddBlankAfterClip::operator()(int currentTime)
{
    //récupérer le clip à traiter
    std::string idClip = "";
    
    Projet& projet = Projet::getInstance();
    
    Timeline timeline = projet.getTimeline();

    bool isClip = timeline.findCurrentClip(idClip,currentTime);
    
    if(!isClip)
        std::cout<< "Clip not found" << std::endl;
    
    else
    {
        //créer la commande 
        IUndoRedoCommand* cmd = new CmdClipAddBlankAfter(idClip,"Commande Add Blank Before Clip "+idClip);

        //trouver le command Manager par le projet

        CommandManager& cmdMng = projet.getCommandManager();

        //ajouter la commande au commande manager
        cmdMng.pushNewCommand(cmd);
    }

    std::cout << "Action done" << std::endl;
    
}


