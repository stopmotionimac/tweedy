#ifndef APPLCIATION_HPP
#define APPLICATION_HPP

#include <tweedy/core/Singleton.hpp>
#include "tweedy/core/Gphoto/Gphoto.hpp"
#include <tweedy/core/Timeline.hpp>
#include <tweedy/core/ChutierMediaExt.hpp>
#include <tweedy/core/Imedia.hpp>
#include <tweedy/core/CommandManager.hpp>


#include<iostream>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>


class Application : public Singleton<Application>
{
  friend class Singleton<Application>;

private:
  Application ()
      : _value (0) { }
  ~Application () { }

public:
  void setValue (int val) { _value = val; }
  int getValue () { return _value; }
  //void setGphotoInstance () { Gphoto::getInstance ();};

  //static boost::ptr_vector<Imedia> getListMedia(){ return listMedia; }
  static boost::ptr_unordered_map<std::string, Imedia*> getMapMedia() {}
  Imedia getImedia(int idMedia) { }
  void addImedia(Imedia * media);
  void supprImedia(int idMedia);
  void printAllMedia();
  void makeChutier();

  static CommandManager& getCommandManager();


private:
  //Gphoto * gPhotoInstance;
  ChutierMediaExt _chutier;
  int _value;

  //static boost::ptr_vector<Imedia> listMedia;
  boost::ptr_unordered_map<std::string, Imedia*> _mapMedia;
  static CommandManager _cmdManager;

};
//to add any media (except MediaExt)
void Application::addImedia(Imedia * media) {
    std::cout<<media->getNameMedia().string()<<std::endl;
    //ImediaType type = media->getImediaType(media);
    _mapMedia[media->getNameMedia().string()] = media;
}

void Application::makeChutier() {
    _chutier.createChutierMediaExt();
    //test import to chutier
    boost::filesystem::path url("projet/mediasExt/test.jpg");
    _chutier.importMediaToChutier(url);
}

void Application::printAllMedia() {
    boost::ptr_unordered_map<std::string, Imedia*>::iterator iter;
    std::cout<<"PRINT MAP APPLI"<<std::endl;
        for (iter = this->_mapMedia.begin(); iter != _mapMedia.end(); ++iter) {
            std::cout<<iter->first<<std::endl;
    }

}

#endif  // APPLICATION_HPP
