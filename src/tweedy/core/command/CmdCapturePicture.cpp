#include <tweedy/core/command/CmdCapturePicture.hpp>
#include <tweedy/core/Projet.hpp>
#include <tweedy/core/Id.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>


CmdCapturePicture::CmdCapturePicture(const std::string& text,const boost::filesystem::path& filename)
        :_text(text),_filename(filename)
{

}

CmdCapturePicture::~CmdCapturePicture()
{
    std::cout << "Dtor cmd : "+_text << std::endl;
}

CmdCapturePicture* CmdCapturePicture::clone() const{
    return new CmdCapturePicture(*this);
}

void CmdCapturePicture::runDo()
{

    Timeline& timeline = Projet::getInstance().getTimeline();

///@todo Why not use CmdInsertClip?

    //créer un nouveau clip
    Clip clip(_filename, timeline.getId() , "clip" + boost::lexical_cast<std::string>(timeline.getNbClip()) );
    timeline.setNbClip( timeline.getNbClip()+1 );

    _newClip = clip;

    //on ajoute le clip au projet
    Projet::getInstance().addImedia(_newClip);
    //on ajoute la photo au chutier des pictures
    boost::filesystem::path filePath(_filename);
    Projet::getInstance().getChutierPictures().importMediaToChutier(filePath);
    std::cout << _filename << std::endl;


    //on ajoute le clip a la fin de la timeline (a regler avec le temps reel)
    clip.setPosition(timeline.getMaxTime(),timeline.getMaxTime()+1);
    timeline.addClip(clip);


}

void CmdCapturePicture::undo()
{
    //recuperer les donnees du clip a supprimer et les "sauvegarder"
    //dans un clip temporaire

    //recuperation du clip grâce a son id
    Projet& projet = Projet::getInstance();
    Timeline& timeline = projet.getTimeline();

    //creation par copy du clip
    _newClip = timeline.mapClip()[_newClip.getId().getIdStringForm()];

    //effacer le clip de la timeline
    timeline.deleteClip(_newClip.getId().getIdStringForm());

    //effacer le blanc de la timeline
    //timeline.deleteBlank(&_newClip);

}

void CmdCapturePicture::redo()
{
    Timeline& timeline = Projet::getInstance().getTimeline();

    //remettre le clip dans la timeline
    _newClip.setPosition(timeline.getMaxTime(),timeline.getMaxTime()+1);
    timeline.addClip(_newClip);
    timeline.updateMaxTime();
}


const std::string& CmdCapturePicture::getText() const {
    return _text;
}
