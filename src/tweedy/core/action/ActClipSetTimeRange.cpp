#include <tweedy/core/action/ActClipSetTimeRange.hpp>
#include <tweedy/core/command/clip/CmdClipSetTimeRange.hpp>
#include <tweedy/core/Projet.hpp>

#include <string>
#include <iostream>
#include <sstream>

ActClipSetTimeRange::ActClipSetTimeRange(int currentTime, const std::string name, int value)
        : IAction(name), _currentTime(currentTime), _value(value)
{
    //récupérer le clip à traiter
    std::string filename = "img/none.jpg";
    
    Application* appli = Application::getInstance();
    
<<<<<<< HEAD
    Timeline timeline = appli->getTimeline();

    bool isClip = timeline.findCurrentClip(filename,_currentTime);
    
    std::cout << timeline.mapClip().size() << std::endl;
    std::cout << isClip << std::endl;
    std::cout << filename << std::endl;
    std::cout << _currentTime << std::endl;
=======
    std::ostringstream oss;
    oss<<_value;
    IUndoRedoCommand* cmd = new CmdClipSetTimeRange(_clip,"Commande Clip Set Time Range"+oss.str()
            , _value);
    
    //trouver le command Manager par l'projet
    
    CommandManager cmdMng = Projet::getCommandManager();
>>>>>>> 186a1c23a9d5acc06c3d3ed2f699962b88f53b80
    
    if(isClip){
        //créer la commande 

        std::ostringstream oss;
        oss<<_value;
        IUndoRedoCommand* cmd = new CmdClipSetTimeRange(filename,"Commande Clip Set Time Range"+oss.str()
                , _value);

        //trouver le command Manager par l'application

        CommandManager& cmdMng = appli->getCommandManager();

        //ajouter la commande au commande manager
        cmdMng.pushNewCommand(cmd);
    }
    else
        std::cout<< "Clip not found" << std::endl;
    
    std::cout << "Action done" << std::endl;
    
}

ActClipSetTimeRange::~ActClipSetTimeRange()
{
    std::cout << "Dtor action clip set time range" << std::endl;
}
