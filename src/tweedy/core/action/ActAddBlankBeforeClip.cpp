#include <tweedy/core/action/ActAddBlankBeforeClip.hpp>
#include <tweedy/core/command/clip/CmdClipAddBlankBefore.hpp>
#include <tweedy/core/Projet.hpp>

#include <string>
#include <iostream>
#include <sstream>

ActAddBlankBeforeClip::ActAddBlankBeforeClip(int currentTime, const std::string name, int value)
        : IAction(name), _currentTime(currentTime), _value(value)
{
    //récupérer le clip à traiter
    std::string filename = "img/none.jpg";
    
    Projet* projet = Projet::getInstance();
    
    Timeline timeline = projet->getTimeline();

    bool isClip = timeline.findCurrentClip(filename,_currentTime);
    
    std::cout << timeline.mapClip().size() << std::endl;
    std::cout << isClip << std::endl;
    std::cout << filename << std::endl;
    std::cout << _currentTime << std::endl;
    
    if(isClip){
        
        //créer la commande 
        IUndoRedoCommand* cmd = new CmdClipAddBlankBefore(filename,"Commande Add Blank Before Clip"+filename
                , 1,true);

        //trouver le command Manager par le projet

        CommandManager& cmdMng = projet->getCommandManager();

        //ajouter la commande au commande manager
        cmdMng.pushNewCommand(cmd);
    }
    else
        std::cout<< "Clip not found" << std::endl;
    
    std::cout << "Action done" << std::endl;
    
}

ActAddBlankBeforeClip::~ActAddBlankBeforeClip()
{
    std::cout << "Dtor action add blank before clip" << std::endl;
}

