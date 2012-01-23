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
  static boost::ptr_unordered_map<std::string, Imedia> getMapMedia() {}
  Imedia getImedia(int idMedia) {  }
  void addImedia(Imedia & media);
  void supprImedia(int idMedia);
  void makeChutier();

private:
  //Gphoto * gPhotoInstance;
  ChutierMediaExt _chutier;
  int _value;
  //static boost::ptr_vector<Imedia> listMedia;
  static boost::ptr_unordered_map<std::string, Imedia> _mapMedia;
  static CommandManager m_cmdManager;

};

void Application::addImedia(Imedia & media) {
    //insert
    //std::string nameMedia = media.getNameMedia().string();
    std::cout<<media.getNameMedia().string()<<std::endl;
    //_mapMedia[nameMedia] = media;
    //std::pair<iterator,bool> insert( key_type& key, mapped_type x )

}

void Application::makeChutier() {
    _chutier.createChutierMediaExt();
}

#endif  // APPLICATION_HPP
