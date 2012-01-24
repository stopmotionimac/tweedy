#ifndef PROJET_HPP
#define PROJET_HPP

#include <tweedy/core/Singleton.hpp>
#include "tweedy/core/Gphoto/Gphoto.hpp"
#include <tweedy/core/Timeline.hpp>
#include <tweedy/core/ChutierMediaExt.hpp>
#include <tweedy/core/Imedia.hpp>
#include <tweedy/core/CommandManager.hpp>
#include <tweedy/core/Timeline.hpp>


#include<iostream>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>


class Projet : public Singleton<Projet>
{
  friend class Singleton<Projet>;

private:
  Projet ()
      : _value (0) { }
  ~Projet () { }

public:
  void setValue (int val) { _value = val; }
  int getValue () { return _value; }
  void setGphotoInstance () { Gphoto::getInstance ();};

  //static boost::ptr_vector<Imedia> getListMedia(){ return listMedia; }
  static boost::ptr_unordered_map<std::string, Imedia*> getMapMedia() {}
  Imedia getImedia(int idMedia) { }
  void addImedia(Imedia * media);
  void supprImedia(int idMedia);
  void printAllMedia();
  void makeChutier();

  //function for gPhotoInstance
  int tryToConnectCamera ();
  bool getValueCameraIsInit();
  void setFolderToSavePictures ();
  void captureToFile();


  CommandManager& getCommandManager();

  Timeline& getTimeline();


private:
  Gphoto * gPhotoInstance;
  ChutierMediaExt _chutier;
  boost::filesystem::path projectFolder;
  int _value;

  //static boost::ptr_vector<Imedia> listMedia;
  boost::ptr_unordered_map<std::string, Imedia*> _mapMedia;

  CommandManager _cmdManager;
  Timeline _timeline;

};
#endif  // PROJET_HPP
