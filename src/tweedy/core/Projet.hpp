#ifndef PROJET_HPP
#define PROJET_HPP

#include <tweedy/core/Singleton.hpp>
#include <tweedy/core/gphoto/Gphoto.hpp>
#include <tweedy/core/Timeline.hpp>
#include <tweedy/core/ChutierMediaExt.hpp>
#include <tweedy/core/Imedia.hpp>
#include <tweedy/core/CommandManager.hpp>
#include <tweedy/core/Timeline.hpp>
#include <tweedy/core/Id.hpp>


#include<iostream>
#include <boost/assign/ptr_map_inserter.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>


class Projet : public Singleton<Projet>
{
  friend class Singleton<Projet>;

private:
  Projet ()
      : _value (0),_id("projet"),_timeline(getId(),"timeline1") { }
  ~Projet () { }

public:
  void setValue (int val) { _value = val; }
  int getValue () { return _value; }
  void setGphotoInstance () { Gphoto::getInstance ();};
  ChutierMediaExt& getChutierMediaExt();
  ChutierMediaExt& getChutierPictures();

  void setValueCameraIsInit (bool val);

  static boost::ptr_unordered_map<std::string, Imedia> getMapMedia() {}
  Imedia getImedia(int idMedia) { }
  boost::filesystem::path getNameImedia (Imedia & imedia);
  void addImedia(Imedia & media);
  void supprImedia(int idMedia);
  void printAllMedia();
  //to suppr
  void fillChutierPicutresWithProjet();

  //function for gPhotoInstance
  int tryToConnectCamera ();
  void setProjectFolder(boost::filesystem::path pathFolder) { _projectFolder =  pathFolder; }
  boost::filesystem::path& getProjectFolder() { return _projectFolder; }
  boost::filesystem::path captureToFile();

  Gphoto& gPhotoInstance() { return Gphoto::getInstance(); }
  
  CommandManager& getCommandManager();
  Timeline& getTimeline();
  
  Id& getId();

  void setProjectFile(boost::filesystem::path projectFile){ _projectFile = projectFile;}
  boost::filesystem::path& getProjectFile() { return _projectFile; }
  
private:
  ChutierMediaExt _chutierMediaExt;
  ChutierMediaExt _chutierPictures;
  boost::filesystem::path _projectFolder;
  boost::filesystem::path _projectFile;
  int _value;

  boost::ptr_unordered_map<std::string, Imedia> _mapMedia;

  CommandManager _cmdManager;
  Timeline _timeline;
  
  Id _id;
  
  friend class boost::serialization::access;
    
  template<class Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
     ar & _timeline;
     ar & _chutierMediaExt;
     std::string s1;
     std::string s2;
     
     if(Archive::is_saving::value)
     {
         s1 = _projectFolder.string();
         s2 = _projectFile.string();
     }    
     ar & boost::serialization::make_nvp("string", s1);
     ar & boost::serialization::make_nvp("string", s2);
     if(Archive::is_loading::value)
     {
         _projectFolder = s1;
         _projectFile = s2;
     }
  }
};
#endif  // PROJET_HPP
