#include <tweedy/core/action/ActClipSetTimeRange.hpp>
#include <tweedy/core/command/clip/CmdClipSetTimeRange.hpp>
#include <tweedy/core/Projet.hpp>

#include <string>
#include <iostream>
#include <sstream>

ActClipSetTimeRange::ActClipSetTimeRange(Clip& clip, const std::string name, double value)
        : IAction(name), _clip(clip), _value(value)
{
    
    //créer la commande 
    
    std::ostringstream oss;
    oss<<_value;
    IUndoRedoCommand* cmd = new CmdClipSetTimeRange(_clip,"Commande Clip Set Time Range"+oss.str()
            , _value);
    
    //trouver le command Manager par l'projet
    
    CommandManager cmdMng = Projet::getCommandManager();
    
    //ajouter la commande au commande manager
    cmdMng.pushNewCommand(cmd);
    
    std::cout << "Action done" << std::endl;
    
}

ActClipSetTimeRange::~ActClipSetTimeRange()
{
    std::cout << "Dtor action clip set time range" << std::endl;
}
