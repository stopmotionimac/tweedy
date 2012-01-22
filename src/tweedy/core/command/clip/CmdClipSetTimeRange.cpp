#include <tweedy/core/command/clip/CmdClipSetTimeRange.hpp>

CmdClipSetTimeRange::CmdClipSetTimeRange(Clip& clip, const std::string& text, double value)
        : _clip(clip),_text(text),_value(value)
{
    
}

CmdClipSetTimeRange::~CmdClipSetTimeRange(){
    
}

CmdClipSetTimeRange* CmdClipSetTimeRange::clone() const{
    return  new CmdClipSetTimeRange(*this);
}

void CmdClipSetTimeRange::runDo(){
    _clip.setTimeOut(_clip.timeOut()+_value);
}

void CmdClipSetTimeRange::redo(){
    this->runDo();
}

void CmdClipSetTimeRange::undo(){
    _clip.setTimeOut(_clip.timeOut()-_value);
}

void CmdClipSetTimeRange::getName() const{
    std::cout<<_text<<std::endl;
}

void CmdClipSetTimeRange::setText(const std::string & newText){
    _text = newText;
}

const std::string& CmdClipSetTimeRange::getText() const {
    return _text;
}
