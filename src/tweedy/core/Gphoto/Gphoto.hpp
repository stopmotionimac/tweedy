#ifndef GPHOTO_HPP
#define GPHOTO_HPP

#include <tweedy/core/Singleton.hpp>

#include <boost/filesystem.hpp>

#ifdef WITH_GPHOTO2
#include <gphoto2/gphoto2.h>
#include "samples.h"
#endif //WITH_GPHOTO2

#include <iostream>

class Gphoto : public Singleton<Gphoto>
{

private:
    Camera * _camera;
    GPContext * _context;
    //const char ** ptr;
    //unsigned long int * size;
    //OK si depuis tweedy
    boost::filesystem::path _fileName;

public:
    Gphoto();
    ~Gphoto();
    void initCamera();
    void tryToConnectCamera();
    void setFolderToSavePictures() { _fileName = "/sandbox/testGPhoto/pictures/";}
    void getSummary();
    void exitCamera();
#ifdef WITH_GPHOTO2
    static void capture_to_file(Camera *camera, GPContext *context, boost::filesystem::path & fn /*const char * fn*/);
    static void errordumper(GPLogLevel level, const char *s, const char *str,void *data);
#endif //WITH_GPHOTO2

private:
#ifdef WITH_GPHOTO2
    void initContext(){_context = sample_create_context();}
#endif //WITH_GPHOTO2


};

Gphoto::~Gphoto() {
#ifdef WITH_GPHOTO2
    gp_camera_exit(_camera, _context);
#endif //WITH_GPHOTO2
#ifndef WITH_GPHOTO2
    std::cout<<"PAS DE LIB GPHOTO2"<<std::endl;
#endif //WITH_GPHOTO2
}

void Gphoto::initCamera() {
#ifdef WITH_GPHOTO2
    initContext();
    //gp_log_add_func(GP_LOG_ERROR, Gphoto::errordumper, NULL);
    gp_camera_new(& _camera);
    int retval = gp_camera_init (_camera, _context);
    if (retval < GP_OK) {
        //printf("No camera auto detected.\n");
        gp_camera_free (_camera);
    }
#endif //WITH_GPHOTO2
#ifndef WITH_GPHOTO2
    std::cout<<"PAS DE LIB GPHOTO2"<<std::endl;
#endif //WITH_GPHOTO2
}

void Gphoto::getSummary() {
#ifdef WITH_GPHOTO2
    CameraText text;
    int retval = gp_camera_get_summary (_camera, &text, _context);
    if (retval < GP_OK) {
        //printf("Camera failed retrieving summary.\n");
        gp_camera_free (_camera);
    }
    //printf("Summary:\n%s\n", text.text);
#endif //WITH_GPHOTO2
#ifndef WITH_GPHOTO2
    std::cout<<"PAS DE LIB GPHOTO2"<<std::endl;
#endif //WITH_GPHOTO2
}

void capture_to_file(Camera *camera, GPContext *context, boost::filesystem::path & fn /*const char * fn*/) {
#ifdef WITH_GPHOTO2
        int fd, retval;
        CameraFile *file;
        CameraFilePath camera_file_path;

        //printf("Capturing.\n");

        /* NOP: This gets overridden in the library to /capt0000.jpg */
        strcpy(camera_file_path.folder, "/");
        strcpy(camera_file_path.name, "foo.jpg");

        retval = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &camera_file_path, context);
        //printf("  Retval: %d\n", retval);

        //printf("Pathname on the camera: %s/%s\n", camera_file_path.folder, camera_file_path.name);

        /*OK si on est dans tweedy!*/
        fn /= camera_file_path.name;
        //std::cout<<fn<<std::endl;
        //fn = camera_file_path.name;
        //caster fn en string!

        //folder/file on computer
        //fd = open(fn, O_CREAT | O_WRONLY, 0644);
        //retval = gp_file_new_from_fd(&file, fd);
        //printf("  Retval: %d\n", retval);
        //retval = gp_camera_file_get(camera, camera_file_path.folder, camera_file_path.name, GP_FILE_TYPE_NORMAL, file, context);
        //printf("  Retval: %d\n", retval);

        //printf("Deleting.\n");
        retval = gp_camera_file_delete(camera, camera_file_path.folder, camera_file_path.name,context);
        //printf("  Retval: %d\n", retval);

        gp_file_free(file);
#endif //WITH_GPHOTO2
#ifndef WITH_GPHOTO2
    std::cout<<"PAS DE LIB GPHOTO2"<<std::endl;
#endif //WITH_GPHOTO2
}

void Gphoto::exitCamera() {
#ifdef WITH_GPHOTO2
    gp_camera_exit(_camera, _context);
#endif //WITH_GPHOTO2
#ifndef WITH_GPHOTO2
    std::cout<<"PAS DE LIB GPHOTO2"<<std::endl;
#endif //WITH_GPHOTO2
}

void Gphoto::errordumper(GPLogLevel level, const char *domain, const char *str,void *data) {
#ifdef WITH_GPHOTO2
  //fprintf(stdout, "%s\n", str);
#endif //WITH_GPHOTO2
#ifndef WITH_GPHOTO2
    std::cout<<"PAS DE LIB GPHOTO2"<<std::endl;
#endif //WITH_GPHOTO2
}

#endif // GPHOTO_HPP
