#ifndef GPHOTO_HPP
#define GPHOTO_HPP

#include <tweedy/core/Singleton.hpp>

#ifdef WITH_GPHOTO2
#include "samples.h"
#include <gphoto2/gphoto2.h>
#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>
#endif //WITH_GPHOTO2

#ifdef WITH_GPHOTO2
#include "samples.h"
#include <gphoto2/gphoto2.h>
#include <gphoto2/gphoto2-port-log.h>
#endif

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <fcntl.h>
#include <iostream>
#include <cstdio>
#include <string>


class Gphoto : public Singleton<Gphoto>
{

private:
    Camera * _camera;
    GPContext * _context;
    bool _cameraIsInit;
    //const char ** ptr;
    //unsigned long int * size;
    boost::filesystem::path _fileName;
    CameraWidget * _mainWidget;
    std::vector<CameraWidget*> _WidgetsVector;

public:
    Gphoto();
    ~Gphoto();

    int initCamera();
    int tryToConnectCamera();
    void setFolderToSavePictures(boost::filesystem::path path) { _fileName = path; _fileName /="projet/pictures/HD"; }

    void findMainWidget();
    CameraWidget * getMainWidget() { findMainWidget(); return _mainWidget; }
    void findChildrenOfOneWidget(CameraWidget* parentWidget);
    std::vector<CameraWidget*>& getWidgetsVector () { return _WidgetsVector; }
    std::string getNameOfAWidget(CameraWidget* widget);
    bool isRadioOrMenu(CameraWidget* widget);
    int CountChoices (CameraWidget* widget);
    std::string getChoice(CameraWidget* widget, int choiceNumber);
    int getTypeWidget(CameraWidget* widget);
    int _lookup_widget(CameraWidget*widget, const char *key, CameraWidget **child);
    void getValue(CameraWidget* widget);
    int get_config_value (Camera *camera, const char *key, char **str, GPContext *context);
    int get_config_value (Camera *camera, const char *key, int * str, GPContext *context);
    void setValueInt(CameraWidget *widget, /*const void **/int value);
    void setValueString(CameraWidget *widget, const void *value);
    int set_config_value (Camera *camera, const char *key, const void * val, GPContext *context);
    void getSummary();
    void exitCamera();
    boost::filesystem::path captureToFile();
    
    std::string doPreview(int i);
    //bool getVarCameraIsInit();
    void setVarCameraIsInit(bool var);


private:
    void initContext();


};

#endif // GPHOTO_HPP
