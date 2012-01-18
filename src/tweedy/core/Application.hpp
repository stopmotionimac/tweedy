#ifndef APPLCIATION_HPP
#define APPLICATION_HPP

#include <tweedy/core/Singleton.hpp>
#include <tweedy/core/Timeline.hpp>
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

  //static boost::ptr_vector<Imedia> getListMedia(){ return listMedia; }
  static boost::ptr_unordered_map<std::string, Imedia> getMapMedia() {}
  static boost::ptr_unordered_map<std::string, Timeline> getMapTimeline() {}
  Imedia getImedia(int idMedia) {  }
  void addImedia(Imedia & media);
  void supprImedia(int idMedia);

private:
  int _value;
  static boost::ptr_vector<Imedia> listMedia;
  static boost::ptr_unordered_map<std::string, Imedia> mapMedia;
  static boost::ptr_unordered_map<std::string, Timeline> mapTimeline;
  static CommandManager m_cmdManager;
};

#endif  // APPLICATION_HPP
