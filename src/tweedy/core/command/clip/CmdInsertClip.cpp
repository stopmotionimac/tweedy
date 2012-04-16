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
    
    //créer un nouveau clip
    Clip clip(_filename, timeline.getId() , "clip" + boost::lexical_cast<std::string>(timeline.getNbClip()) );
    timeline.setNbClip( timeline.getNbClip()+1 );
	
    _clipTemp = clip;
    
    //inserer le clip dans la timeline a la nouvelle position
    timeline.insertClip(_clipTemp, _newPosition);
}

void CmdInsertClip::redo(){
   
    Projet::getInstance().getTimeline().insertClip(_clipTemp, _newPosition);
    
}

void CmdInsertClip::undo(){
    
    //recuperer les donnees du clip a supprimer et les "sauvegarder"
    //dans un clip temporaire
    
    //recuperation du clip grâce a son id
    Projet& projet = Projet::getInstance();
    Timeline& timeline = projet.getTimeline();
    const Clip& clip = timeline.mapClip()[_clipTemp.getId().getIdStringForm()];

    //creation par copy du clip
    _clipTemp = clip;
    
    //effacer le clip de la timeline
    timeline.deleteClip(_clipTemp.getId().getIdStringForm());
            
}


const std::string& CmdInsertClip::getText() const {
    return _text;
}
