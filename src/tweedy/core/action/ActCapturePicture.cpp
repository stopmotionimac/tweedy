#include <tweedy/core/action/ActCapturePicture.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/command/CmdCapturePicture.hpp>

ActCapturePicture::ActCapturePicture()
        :IAction("Action capture picture")
{
    
}

ActCapturePicture::~ActCapturePicture()
{
    
}

void ActCapturePicture::operator ()()
{
    
    Projet& project = Projet::getInstance();
    project.setFolderToSavePictures();
    
    //recuperer le filename de la picture
    boost::filesystem::path filename = project.captureToFile();
    
    //creation d'une commande de suppression de clip
    //std::cout<<"AVT LIGNE 26"<<std::endl;
    IUndoRedoCommand* cmd = new CmdCapturePicture("Command Capture Picture ",filename);
    //std::cout<<"APRES LIGNE 26"<<std::endl;

    //ajout de la commande au commande manager
    CommandManager& cmdMng = project.getCommandManager();
    cmdMng.pushNewCommand(cmd);
    
    std::cout << "Action done" << std::endl;
}
