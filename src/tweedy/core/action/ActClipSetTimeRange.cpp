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

    //find the command manager thanks to the application (core)
    CommandManager& cmdMng = projet.getCommandManager();

    //add the command to the command manager
    cmdMng.pushNewCommand(cmd);
    
}
