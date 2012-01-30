#include <tweedy/core/command/clip/CmdInsertClip.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/Timeline.hpp>


CmdInsertClip::CmdInsertClip(const std::string& idClip, const std::string& text, int newPosition)
        : _idClip(idClip),_text(text),_newPosition(newPosition)
{
    
}

CmdInsertClip::~CmdInsertClip(){

}

CmdInsertClip* CmdInsertClip::clone() const{
    return  new CmdInsertClip(*this);
}



void CmdInsertClip::runDo(){
    
    
    Timeline& timeline = Projet::getInstance().getTimeline();
    
    //inserer le clip dans la timeline a la nouvelle position
    timeline.insertClip(_idClip, _newPosition);
}

void CmdInsertClip::redo(){
    
    //re inserer le clip a la nouvelle position
    //ajouter le clip temp dans la map
    Timeline& timeline = Projet::getInstance().getTimeline();
    timeline.addClip(_clipTemp);
    
}

void CmdInsertClip::undo(){
    
    //recuperer les donnees du clip a supprimer et les "sauvegarder"
    //dans un clip temporaire
    
    //recuperation du clip grâce a son id
    Projet& projet = Projet::getInstance();
    Timeline& timeline = projet.getTimeline();
    const Clip& clip = timeline.mapClip()[_idClip];

    //creation par copy du clip
    _clipTemp = clip;
    
    //effacer le clip de la timeline
    timeline.deleteClip(_idClip);
    
}


const std::string& CmdInsertClip::getText() const {
    return _text;
}
