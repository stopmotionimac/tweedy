#ifndef SINGLETON_HPP
#define SINGLETON_HPP

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
  ~Singleton () { }

public:
  static T& getInstance ()
  {
    if (NULL == _singleton)
      {
        _singleton = new T;
      }
    else
      {
      }

    return *_singleton;
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
#endif  // SINGLETON_HPP
