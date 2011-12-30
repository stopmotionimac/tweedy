#ifndef APPLCIATION_HPP
#define APPLICATION_HPP

#include <tweedy/core/Singleton.hpp>
#include <tweedy/core/Imedia.hpp>

#include<iostream>
#include <boost/ptr_container/ptr_vector.hpp>


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

  static boost::ptr_vector<Imedia> getListMedia(){ return listMedia; }
  Imedia getImedia(int idMedia) { return listMedia[idMedia]; }
  void addImedia(Imedia & media);
  void supprImedia(int idMedia);

private:
  int _value;
  static boost::ptr_vector<Imedia> listMedia;
};

#endif  // APPLICATION_HPP
