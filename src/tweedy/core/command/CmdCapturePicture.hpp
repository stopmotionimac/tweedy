#ifndef CMDCAPTUREPICTURE_HPP
#define	CMDCAPTUREPICTURE_HPP

#include <tweedy/core/command/IUndoRedoCommand.hpp>
#include <boost/filesystem.hpp>
#include <tweedy/core/Clip.hpp>

class CmdCapturePicture : public IUndoRedoCommand
{
    
public:

    CmdCapturePicture(const std::string& ,const boost::filesystem::path&);
    ~CmdCapturePicture();

    CmdCapturePicture* clone() const;


    void undo();
    void runDo();
    void redo();

    const std::string& getText() const;
    
private:

   std::string _text;
   boost::filesystem::path _filename;
   Clip _newClip;
};

#endif	/* CMDCAPTUREPICTURE_HPP */

