#include <tweedy/core/action/ActClipSetTimeRange.hpp>
#include <tweedy/core/command/clip/CmdClipSetTimeRange.hpp>
#include <tweedy/core/Projet.hpp>

#include <string>
#include <iostream>
#include <sstream>

ActClipSetTimeRange::ActClipSetTimeRange()
        :IAction("Action set time range clip")
{
    
}

void ActClipSetTimeRange::operator()(int currentTime, int value)
{
    //récupérer le clip à traiter
    std::string filename = "img/none.jpg";
    
    Projet& projet = Projet::getInstance();
    
    Timeline timeline = projet.getTimeline();

    bool isClip = timeline.findCurrentClip(filename,currentTime);
    
    
    if(!isClip)
        
        std::cout<< "Clip not found" << std::endl;
     
    else{
        //créer la commande 

        std::ostringstream oss;
        oss<<value;
        IUndoRedoCommand* cmd = new CmdClipSetTimeRange(filename,"Commande Clip Set Time Range"+oss.str()
                , value);

        //trouver le command Manager par l'application

        CommandManager& cmdMng = projet.getCommandManager();

        //ajouter la commande au commande manager
        cmdMng.pushNewCommand(cmd);
    }
    
    std::cout << "Action done" << std::endl;
    
}

ActClipSetTimeRange::~ActClipSetTimeRange()
{
    std::cout << "Dtor action : " +_name << std::endl;
}
