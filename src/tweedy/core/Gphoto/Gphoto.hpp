#ifndef GPHOTO_HPP
#define GPHOTO_HPP

#include <tweedy/core/Singleton.hpp>

#ifdef WITH_GPHOTO2
#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>
#endif

#include <boost/filesystem.hpp>

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
    void setFolderToSavePictures() { _fileName = "projet/pictures/";}
    void getSummary();
    void exitCamera();
    void captureToFile();


private:
    void initContext();


};

#endif // GPHOTO_HPP
