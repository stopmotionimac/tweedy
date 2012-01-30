#include <tweedy/core/action/ActDragNDropChutToTL.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/command/clip/CmdInsertClip.hpp>

ActDragNDropChutToTL::ActDragNDropChutToTL()
        :IAction("Action Drag and Drop from Chutier to Timeline")
{
    
}


ActDragNDropChutToTL::~ActDragNDropChutToTL()
{
    
}

void ActDragNDropChutToTL::operator ()(const std::string& idClip, int position)
{
    
    Projet& project = Projet::getInstance();
    
    //creation de la commande de deplacement d'un clip dans la timeline
    IUndoRedoCommand* cmd = new CmdInsertClip(idClip,"Cmd Insert Clip : "+idClip, position);
    
    //ajout de la commande au commande manager
    CommandManager& cmdMng = project.getCommandManager();
    cmdMng.pushNewCommand(cmd);
    
    std::cout << "Action done" << std::endl;
    
}
