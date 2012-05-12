#include <tweedy/core/command/clip/CmdClipDelete.hpp>
#include <tweedy/core/Singleton.hpp>
#include <tweedy/core/Projet.hpp>

CmdClipDelete::CmdClipDelete(const std::string& idClip, const std::string& text)
        : _idClip(idClip),_text(text)
{

}

CmdClipDelete::~CmdClipDelete()
{
    //destroy temporary clip
}

CmdClipDelete* CmdClipDelete::clone() const{
    return  new CmdClipDelete(*this);
}

void CmdClipDelete::runDo(){
    //get clip data to suppr and save it
    
    //get clip back thanks to its id
    Projet& projet = Projet::getInstance();
    Timeline& timeline = projet.getTimeline();
    
    //creation of clip by copy
    _clipTemp = timeline.mapClip()[_idClip];

    //suppr clip from the timeline
    timeline.deleteClip(_idClip);
}

void CmdClipDelete::undo()
{
    //add temporary clip on the map
    Timeline& timeline = Projet::getInstance().getTimeline();
    timeline.unselectAll();
    timeline.insertClip(_clipTemp, _clipTemp.timeIn());
}

void CmdClipDelete::redo()
{
    //remove clip from the map
    Timeline& timeline = Projet::getInstance().getTimeline();
    timeline.deleteClip(_clipTemp.getId().getIdStringForm());
}

const std::string& CmdClipDelete::getText() const {
    return _text;
}
