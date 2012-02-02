#include <tweedy/core/command/clip/CmdBlankDelete.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/Timeline.hpp>



CmdBlankDelete::CmdBlankDelete(int currentTime, const std::string& text)
        : _currentTime(currentTime),_text(text)
{
    
}


CmdBlankDelete::~CmdBlankDelete()
{
    //destruction du clip temporaire
    std::cout<< "Dtor cmd delete blank" << std::endl;
}

CmdBlankDelete* CmdBlankDelete::clone() const{
    return  new CmdBlankDelete(*this);
}


void CmdBlankDelete::runDo(){
    
    //supprimer le blanc au temps courant
    Timeline& timeline = Projet::getInstance().getTimeline();
    timeline.deleteBlank(_currentTime);
    
}

void CmdBlankDelete::undo()
{
    //afficher le blanc au temps courant
    //recuperer le premier clip après le temps courant
    Timeline& timeline = Projet::getInstance().getTimeline();
    
    std::string idClip;
    int currentTimeTemp = _currentTime;
    
    //tant qu'on ne trouve pas le premier clip et qu'on reste dans la timeline
    while(!timeline.findCurrentClip(idClip,currentTimeTemp) && currentTimeTemp <= timeline.maxTime())
    {
        ++currentTimeTemp;
    }
    
    //lorsqu'on sort de la boucle
    //si l'on a pas trouvé de clip
    if(currentTimeTemp > timeline.maxTime())
    {
        currentTimeTemp = _currentTime-1;
        //on doit trouver le clip avant le temps courant
        while(!timeline.findCurrentClip(idClip,currentTimeTemp) && currentTimeTemp >= 0)
        {
            --currentTimeTemp;
        }
        
        //si on n'a pas trouvé de clip avant
        if (currentTimeTemp < 0)
            //on reduit la taille de la timeline
            std::cout<< "Timeline reduite" << std::endl;
        
        else{
            //on ajoute un blanc après le clip precedent
            timeline.addBlank(idClip,false);
        }
    }
    else
    {
        //on ajoute un blanc avant le clip suivant
        timeline.addBlank(idClip,true);
    }
        
    
}

void CmdBlankDelete::redo()
{
    //supprimer le blanc au temps courant
    this->runDo();
}

const std::string& CmdBlankDelete::getText() const {
    return _text;
}