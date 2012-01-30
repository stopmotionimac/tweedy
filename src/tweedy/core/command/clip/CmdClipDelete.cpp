#include <tweedy/core/command/clip/CmdClipDelete.hpp>
#include <tweedy/core/Singleton.hpp>
#include <tweedy/core/Projet.hpp>

CmdClipDelete::CmdClipDelete(const std::string& idClip, const std::string& text)
        : _idClip(idClip),_text(text)
{
    
}

CmdClipDelete::~CmdClipDelete()
{
    //destruction du clip temporaire
    std::cout<< "Dtor cmd delete clip" << std::endl;
}

CmdClipDelete* CmdClipDelete::clone() const{
    return  new CmdClipDelete(*this);
}

void CmdClipDelete::runDo(){
    
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

void CmdClipDelete::undo()
{
    //ajouter le clip temp dans la map
    Timeline& timeline = Projet::getInstance().getTimeline();
    timeline.addClip(_clipTemp);
}

void CmdClipDelete::redo()
{
    //retirer le clip de la map
    Timeline& timeline = Projet::getInstance().getTimeline();
    timeline.deleteClip(_clipTemp.imgPath().string());
}

const std::string& CmdClipDelete::getText() const {
    return _text;
}