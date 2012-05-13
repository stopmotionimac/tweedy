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

    //creattion of a command for suppr clip
    IUndoRedoCommand* cmd = new CmdCapturePicture("Command Capture Picture ",filename);

    //add the command to the comand manager
    CommandManager& cmdMng = project.getCommandManager();
    cmdMng.pushNewCommand(cmd);
    
}
