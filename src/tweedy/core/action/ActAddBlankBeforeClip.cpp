#include <tweedy/core/action/ActAddBlankBeforeClip.hpp>
#include <tweedy/core/command/clip/CmdClipAddBlankBefore.hpp>
#include <tweedy/core/Projet.hpp>

#include <string>
#include <iostream>
#include <sstream>

ActAddBlankBeforeClip::ActAddBlankBeforeClip()
        :IAction("Action add blank before clip")
{
    
}


ActAddBlankBeforeClip::~ActAddBlankBeforeClip()
{
    std::cout << "Dtor action : "+_name << std::endl;
}



void ActAddBlankBeforeClip::operator()(int currentTime)
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
        IUndoRedoCommand* cmd = new CmdClipAddBlankBefore(idClip,"Commande Add Blank Before Clip "+idClip);

        //trouver le command Manager par le projet

        CommandManager& cmdMng = projet.getCommandManager();

        //ajouter la commande au commande manager
        cmdMng.pushNewCommand(cmd);
    }
    
    std::cout << "Action done" << std::endl;
    
}


