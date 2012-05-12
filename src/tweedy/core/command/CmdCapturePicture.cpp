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

}

CmdCapturePicture* CmdCapturePicture::clone() const{
    return new CmdCapturePicture(*this);
}

void CmdCapturePicture::runDo()
{
    Timeline& timeline = Projet::getInstance().getTimeline();

    //create a new clip
    Clip clip(_filename, timeline.getId() , "clip" + boost::lexical_cast<std::string>(timeline.getNbClip()) );
    timeline.setNbClip( timeline.getNbClip()+1 );

    _newClip = clip;

    //add the clip to the project
    Projet::getInstance().addImedia(_newClip);
    //add the picture to pictures' chutier
    boost::filesystem::path filePath(_filename);
    Projet::getInstance().getChutierPictures().importMediaToChutier(filePath);

    //add the clip to the end of the timeline (real time?)
    clip.setPosition(timeline.getMaxTime(),timeline.getMaxTime()+1);
    timeline.insertClip(clip, clip.timeIn());
}

void CmdCapturePicture::undo()
{
    //get back clip thanks to its id
    Projet& projet = Projet::getInstance();
    Timeline& timeline = projet.getTimeline();

    //creation of clip by copy
    _newClip = timeline.mapClip()[_newClip.getId().getIdStringForm()];

    //suprr the clip from the timeline
    timeline.deleteClip(_newClip.getId().getIdStringForm());
}

void CmdCapturePicture::redo()
{
    Timeline& timeline = Projet::getInstance().getTimeline();

    //put back the clip in the timeline
    _newClip.setPosition(timeline.getMaxTime(),timeline.getMaxTime()+1);
    timeline.insertClip(_newClip, _newClip.timeIn());
}

const std::string& CmdCapturePicture::getText() const {
    return _text;
}
