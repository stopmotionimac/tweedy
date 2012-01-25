#include <tweedy/core/command/clip/CmdClipAddBlankAfter.hpp>


#include <tweedy/core/Timeline.hpp>

#include <tweedy/core/Projet.hpp>

CmdClipAddBlankAfter::CmdClipAddBlankAfter(const std::string& idClip, const std::string& text, 
        double value,bool blankb, bool blanka) : _idClip(idClip),_text(text),
        _value(value),_blankb(blankb),_blanka(blanka)
{
    
}

CmdClipAddBlankAfter::~CmdClipAddBlankAfter(){
    
}

CmdClipAddBlankAfter* CmdClipAddBlankAfter::clone() const{
    return  new CmdClipAddBlankAfter(*this);
}

void CmdClipAddBlankAfter::runDo(){
    
    Projet& projet = Projet::getInstance();
    std::cout << _idClip << _value << std::endl;
    projet.getTimeline().addTimeToClip(_idClip,_value,_blankb,_blanka);

}

void CmdClipAddBlankAfter::redo(){
    this->runDo();
    std::cout << "redo" << std::endl;
}

void CmdClipAddBlankAfter::undo(){
    
    Projet& projet = Projet::getInstance();
    int timeOut =projet.getTimeline().mapClip()[_idClip].timeOut();
    projet.getTimeline().deleteBlank(timeOut+1);
    

    std::cout << "undo" << std::endl;
}

void CmdClipAddBlankAfter::getName() const{
    std::cout<<_text<<std::endl;
}

void CmdClipAddBlankAfter::setText(const std::string & newText){
    _text = newText;
}

const std::string& CmdClipAddBlankAfter::getText() const {
    return _text;
}
