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

void ActCapturePicture::operator ()(const std::string filename)
{
    
    Projet& project = Projet::getInstance();
    /*
    project.gPhotoInstance().setFolderToSavePictures(project.getProjectFolder());
    
    //recuperer le filename de la picture
    boost::filesystem::path filename = project.gPhotoInstance().captureToFile();
    */
    //creation d'une commande de suppression de clip
    IUndoRedoCommand* cmd = new CmdCapturePicture("Command Capture Picture ",filename);

    //ajout de la commande au commande manager
    CommandManager& cmdMng = project.getCommandManager();
    cmdMng.pushNewCommand(cmd);
    
    std::cout << "Action done" << std::endl;
}
