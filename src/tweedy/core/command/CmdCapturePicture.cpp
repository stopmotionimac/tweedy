#include <tweedy/core/command/CmdCapturePicture.hpp>
#include <tweedy/core/Projet.hpp>


CmdCapturePicture::CmdCapturePicture(const std::string& text,const boost::filesystem::path& url)
        :_text(text),_newClip(url)
{
    
}

CmdCapturePicture::~CmdCapturePicture()
{
    std::cout << "Dtor cmd : "+_text << std::endl;
}

CmdCapturePicture* CmdCapturePicture::clone() const{
    return  new CmdCapturePicture(*this);
}

void CmdCapturePicture::runDo()
{
    //on ajoute le clip au projet
    Projet::getInstance().addImedia(_newClip);
    
    
    Timeline& timeline = Projet::getInstance().getTimeline();
    
    //on ajoute le clip a la fin de la timeline (a regler avec le temps reel)
    _newClip.setPosition(timeline.maxTime(),timeline.maxTime()+1);
    timeline.addClip(_newClip);
    timeline.setMaxTime();
    
    
}

void CmdCapturePicture::undo()
{ 
    //effacer le clip de la timeline
    Projet::getInstance().getTimeline().deleteClip(_newClip.imgPath().string());
}

void CmdCapturePicture::redo()
{
    //remettre le clip dans la timeline
    Projet::getInstance().getTimeline().addClip(_newClip);
}


const std::string& CmdCapturePicture::getText() const {
    return _text;
}