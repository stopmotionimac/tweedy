#include <tweedy/core/command/clip/CmdInsertClip.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/Timeline.hpp>
#include <boost/lexical_cast.hpp>


CmdInsertClip::CmdInsertClip(const std::string& filename, const std::string& text, int newPosition)
        : _filename(filename),_text(text),_newPosition(newPosition)
{

}

CmdInsertClip::~CmdInsertClip(){

}

CmdInsertClip* CmdInsertClip::clone() const{
    return  new CmdInsertClip(*this);
}

void CmdInsertClip::runDo(){
    Timeline& timeline = Projet::getInstance().getTimeline();
    
    //create a new clip
    Clip clip(_filename, timeline.getId() , "clip" + boost::lexical_cast<std::string>(timeline.getNbClip()) );
    timeline.setNbClip( timeline.getNbClip()+1 );
	
    _clipTemp = clip;
    _clipTemp.setPosition(_newPosition, _newPosition+1);

    //put the clip into the timeline at the new position
    timeline.insertClip(_clipTemp, _newPosition);
}

void CmdInsertClip::redo(){
    Projet::getInstance().getTimeline().insertClip(_clipTemp, _newPosition);
}

void CmdInsertClip::undo(){
    //take the data of the clip to suppr and save it
    
    //get back the clip thanks to its id
    Projet& projet = Projet::getInstance();
    Timeline& timeline = projet.getTimeline();
    const Clip& clip = timeline.mapClip()[_clipTemp.getId().getIdStringForm()];

    //creation of a clip by copy
    _clipTemp = clip;
    
    //suppr the clip from the timeline
    timeline.deleteClip(_clipTemp.getId().getIdStringForm());
            
}

const std::string& CmdInsertClip::getText() const {
    return _text;
}
