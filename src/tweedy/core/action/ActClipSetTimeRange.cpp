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


ActClipSetTimeRange::~ActClipSetTimeRange()
{
    std::cout << "Dtor action : " +_name << std::endl;
}



void ActClipSetTimeRange::operator()(int currentTime, int value)
{
    Projet& projet = Projet::getInstance();
    Timeline timeline = projet.getTimeline();

    std::string idClip = timeline.findCurrentClip(currentTime);

    std::ostringstream oss;
    oss<<value;
    IUndoRedoCommand* cmd = new CmdClipSetTimeRange(idClip,"Commande Clip Set Time Range"+oss.str()
    , value);
    //trouver le command Manager par l'application

    CommandManager& cmdMng = projet.getCommandManager();

    //ajouter la commande au commande manager
    cmdMng.pushNewCommand(cmd);

    std::cout << "Action done" << std::endl;
    
}


