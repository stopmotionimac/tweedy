#ifndef GPHOTO_HPP
#define GPHOTO_HPP

#include <iostream>
#include <boost/filesystem.hpp>
#include <tweedy/core/Singleton.hpp>
#include <gphoto2/gphoto2.h>


class Gphoto : public Singleton<Gphoto>
{

private:
    Camera * _camera;
    GPContext * _context;
    //const char ** ptr;
    //unsigned long int * size;
    //OK si depuis tweedy
    boost::filesystem::path fileName;

public:
    Gphoto();
    ~Gphoto();
    initCamera();
    tryToConnectCamera();
    setFolderToSavePictures() {fileName( "/sandbox/testGPhoto/pictures/" );}
    getSummary();
    exitCamera();
    caturePictures();

private:
    initContext(){_context = sample_create_context();}

};

Gphoto::~Gphoto() {
    gp_camera_exit(_camera, _context);
}

Gphoto::initCamera() {
    initContext();
    gp_log_add_func(GP_LOG_ERROR, errordumper, NULL);
    gp_camera_new(& _camera);
    int retval = gp_camera_init (_camera, _context);
    if (retval < GP_OK) {
        //printf("No camera auto detected.\n");
        gp_camera_free (_camera);
    }
}

Gphoto::getSummary() {
    int retval = gp_camera_get_summary (_camera, &text, _context);
    if (retval < GP_OK) {
        //printf("Camera failed retrieving summary.\n");
        gp_camera_free (_camera);
        return 0;
    }
    //printf("Summary:\n%s\n", text.text);
}

Gphoto::capturePictures() {
    //setFolderToSavePictures();
    capture_to_file(_camera, _context, _fileName);
}

Gphoto::exitCamera() {
    gp_camera_exit(_camera, _context);
}

#endif // GPHOTO_HPP
