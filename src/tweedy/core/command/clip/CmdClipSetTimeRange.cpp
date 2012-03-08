#include <tweedy/core/command/clip/CmdClipSetTimeRange.hpp>

#include <tweedy/core/Timeline.hpp>

#include <tweedy/core/Projet.hpp>

CmdClipSetTimeRange::CmdClipSetTimeRange(const std::string& idClip, const std::string& text, double value)
        : _idClip(idClip),_text(text),_value(value)
{
    
}

CmdClipSetTimeRange::~CmdClipSetTimeRange(){

}

CmdClipSetTimeRange* CmdClipSetTimeRange::clone() const{
    return  new CmdClipSetTimeRange(*this);
}

void CmdClipSetTimeRange::runDo(){
    
    Projet& projet = Projet::getInstance();
    std::cout << _idClip << _value << std::endl;
    projet.getTimeline().addTimeToClip(_idClip,_value);
    std::cout << projet.getTimeline().getMaxTime() << std::endl;
    
    //_clip.setTimeOut(_clip.timeOut()+_value);
}

void CmdClipSetTimeRange::redo(){
    this->runDo();
    std::cout << "redo" << std::endl;
}

void CmdClipSetTimeRange::undo(){
    
    Projet& projet = Projet::getInstance();
    projet.getTimeline().addTimeToClip(_idClip,-_value);
    
    std::cout << projet.getTimeline().getMaxTime() << std::endl;

    std::cout << "undo" << std::endl;
}


const std::string& CmdClipSetTimeRange::getText() const {
    return _text;
}
