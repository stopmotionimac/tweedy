#ifndef GPHOTO_HPP
#define GPHOTO_HPP

#include <tweedy/core/Singleton.hpp>

#include <boost/filesystem.hpp>

#ifdef WITH_GPHOTO2
#include "samples.h"
#include <gphoto2/gphoto2.h>
#endif //WITH_GPHOTO2

#include <fcntl.h>
#include <iostream>


class Gphoto : public Singleton<Gphoto>
{

private:
    Camera * _camera;
    GPContext * _context;
    bool _cameraIsInit;
    //const char ** ptr;
    //unsigned long int * size;
    boost::filesystem::path _fileName;

public:
    Gphoto();
    ~Gphoto();
    void initCamera();
    void tryToConnectCamera();
    //sera changé en fonction du choix de l'utilisateur pour son dossier de save
    void setFolderToSavePictures() { _fileName = "/projet/pictures/";}
    void getSummary();
    void exitCamera();
#ifdef WITH_GPHOTO2
    static void capture_to_file(Camera *camera, GPContext *context, boost::filesystem::path & fn /*const char * fn*/);
    static void errordumper(GPLogLevel level, const char *s, const char *str,void *data);
#endif //WITH_GPHOTO2

private:
    void initContext();


};

#endif // GPHOTO_HPP
