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
  ~Singleton () { std::cout << "destroying singleton." << std::endl; }

public:
  static T& getInstance ()
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
