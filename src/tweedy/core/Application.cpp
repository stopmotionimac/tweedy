#include "Application.hpp"

Application* Application::application = NULL;

/*Application::Application()
{
}
*/

Application& Application::getApplication()
{
    if( application == NULL )
    {
        application = new Application();
    }
    else
    {
        std::cout<<"The application's instance already exist"<<std::endl;
    }
    return *application;
}


