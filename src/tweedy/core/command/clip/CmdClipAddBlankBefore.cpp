#include <tweedy/core/command/clip/CmdClipAddBlankBefore.hpp>


#include <tweedy/core/Timeline.hpp>

#include <tweedy/core/Projet.hpp>

CmdClipAddBlankBefore::CmdClipAddBlankBefore(const std::string& idClip, const std::string& text) 
: _idClip(idClip),_text(text) {

}


CmdClipAddBlankBefore::~CmdClipAddBlankBefore(){
    
}

CmdClipAddBlankBefore* CmdClipAddBlankBefore::clone() const{
    return  new CmdClipAddBlankBefore(*this);
}

void CmdClipAddBlankBefore::runDo(){
    
    Projet& projet = Projet::getInstance();
    std::cout << _idClip << _value << std::endl;
    projet.getTimeline().addBlank(_idClip,true);

}

void CmdClipAddBlankBefore::redo(){
    this->runDo();
    std::cout << "redo" << std::endl;
}

void CmdClipAddBlankBefore::undo(){
    
    Projet& projet = Projet::getInstance();
    int timeIn =projet.getTimeline().mapClip()[_idClip].timeIn();
    projet.getTimeline().deleteBlank(timeIn-1);
    

    std::cout << "undo" << std::endl;
}

const std::string& CmdClipAddBlankBefore::getText() const {
    return _text;
}
