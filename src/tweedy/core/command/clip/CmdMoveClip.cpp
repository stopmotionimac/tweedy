#include <tweedy/core/command/clip/CmdMoveClip.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/Timeline.hpp>

CmdMoveClip::CmdMoveClip(const std::string& idClip, const std::string& text, int newPosition)
        : _idClip(idClip),_text(text),_newPosition(newPosition)
{
    //stock old version of the clip
    _oldPosition = Projet::getInstance().getTimeline().mapClip()[_idClip].timeIn();
}

CmdMoveClip::~CmdMoveClip(){

}

CmdMoveClip* CmdMoveClip::clone() const{
    return  new CmdMoveClip(*this);
}

void CmdMoveClip::runDo(){
    Timeline& timeline = Projet::getInstance().getTimeline();
    //move clip to the new position
    timeline.moveElement(_idClip, _newPosition);
}

void CmdMoveClip::redo(){
    //move clip to the new position
    this->runDo();
    
}

void CmdMoveClip::undo(){
    Timeline& timeline = Projet::getInstance().getTimeline();
    //move clip to its old position
    timeline.moveElement(_idClip,_oldPosition);
    
}

const std::string& CmdMoveClip::getText() const {
    return _text;
}
