#include "Application.hpp"

Application::application = NULL;

/*Application::Application()
{
}
*/

Application::getApplication() {
    if (application == NULL) {
        static Application application;
    }
    else {
        std::cout<<"The application's instance already exist"<<std::endl;
    }
    return application;
}
