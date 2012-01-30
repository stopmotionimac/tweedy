#include <tweedy/core/command/clip/CmdMoveClip.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/Timeline.hpp>

CmdMoveClip::CmdMoveClip(const std::string& idClip, const std::string& text, int newPosition)
        : _idClip(idClip),_text(text),_newPosition(newPosition)
{
    
    //stocker l'ancienne position du clip
    _oldPosition = Projet::getInstance().getTimeline().mapClip()[_idClip].timeIn();
}

CmdMoveClip::~CmdMoveClip(){

}

CmdMoveClip* CmdMoveClip::clone() const{
    return  new CmdMoveClip(*this);
}



void CmdMoveClip::runDo(){
    
    
    Timeline& timeline = Projet::getInstance().getTimeline();
    
    //deplacer le clip a la nouvelle position
    timeline.moveElement(_idClip, _newPosition);
}

void CmdMoveClip::redo(){
    
    //deplacer le clip a la nouvelle position
    this->runDo();
    
}

void CmdMoveClip::undo(){
    
    Timeline& timeline = Projet::getInstance().getTimeline();
    
    //deplacer le clip a son ancienne position
    timeline.moveElement(_idClip,_oldPosition);
    
}


const std::string& CmdMoveClip::getText() const {
    return _text;
}