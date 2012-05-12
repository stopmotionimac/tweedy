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
    projet.getTimeline().addTimeToClip(_idClip,_value);
}

void CmdClipSetTimeRange::redo(){
    this->runDo();
}

void CmdClipSetTimeRange::undo(){
    Projet& projet = Projet::getInstance();
    projet.getTimeline().addTimeToClip(_idClip,-_value);
}

const std::string& CmdClipSetTimeRange::getText() const {
    return _text;
}
