#include <tweedy/core/action/ActDragNDropTLToTL.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/command/clip/CmdMoveClip.hpp>

ActDragNDropTLToTL::ActDragNDropTLToTL()
        :IAction("Action Drag and Drop from Timeline to Timeline")
{
    
}


ActDragNDropTLToTL::~ActDragNDropTLToTL()
{
    
}

void ActDragNDropTLToTL::operator ()(const std::string& idClip, int position)
{
    
    Projet& project = Projet::getInstance();
    
    //creation de la commande de deplacement d'un clip dans la timeline
    IUndoRedoCommand* cmd = new CmdMoveClip(idClip,"Cmd Move Clip : "+idClip, position);
    
    //ajout de la commande au commande manager
    CommandManager& cmdMng = project.getCommandManager();
    cmdMng.pushNewCommand(cmd);
    
    std::cout << "Action done" << std::endl;
    
}