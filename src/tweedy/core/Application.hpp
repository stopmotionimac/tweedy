#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>

class Application
{
private:
    static Application application;

public:
    static Application getApplication();

private:
    Application();
    //~Application();
};

#endif // APPLICATION_HPP
