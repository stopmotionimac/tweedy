#ifndef APPLCIATION_HPP
#define APPLICATION_HPP

#include "Imedia.hpp"

#include<iostream>
#include <boost/ptr_container/ptr_vector.hpp>

//
//Singleton to any class
//

template <typename T>
class Singleton
{
protected:
  // Constructor/destructor
  Singleton () { }
  ~Singleton () { std::cout << "destroying singleton." << std::endl; }

public:
  static T *getInstance ()
  {
    if (NULL == _singleton)
      {
        std::cout << "creating singleton." << std::endl;
        _singleton = new T;
      }
    else
      {
        std::cout << "singleton already exist" << std::endl;
      }

    return (static_cast<T*> (_singleton));
  }

  static void kill ()
  {
    if (NULL != _singleton)
      {
        delete _singleton;
        _singleton = NULL;
      }
  }

private:
  static T *_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = NULL;

//
//

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

private:
  int _value;
  static boost::ptr_vector<Imedia> listMedia;
};

#endif  // APPLICATION_HPP
