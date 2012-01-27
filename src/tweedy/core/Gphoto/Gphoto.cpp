#include "Gphoto.hpp"

#ifdef WITH_GPHOTO2
#include "samples.h"
#include <gphoto2/gphoto2.h>
#include <gphoto2/gphoto2-port-log.h>
#endif

#include <iostream>

#ifdef WITH_GPHOTO2

static boost::filesystem::path capture_to_file( Camera *camera, GPContext *context, boost::filesystem::path & fn )
{
	int fd, retval;
	CameraFile *file;
	CameraFilePath camera_file_path;

	//printf("Capturing.\n");

	/* NOP: This gets overridden in the library to /capt0000.jpg */
	strcpy( camera_file_path.folder, "/" );
	strcpy( camera_file_path.name, "foo.jpg" );
	retval = gp_camera_capture( camera, GP_CAPTURE_IMAGE, &camera_file_path, context );
	//printf("  Retval: %d\n", retval);

	//printf("Pathname on the camera: %s/%s\n", camera_file_path.folder, camera_file_path.name);

	fn /= camera_file_path.name;
	const char * fnToOpen = fn.string().data();
	std::cout << fnToOpen << std::endl;

	//folder/file on computer
	fd = open( fnToOpen, O_CREAT | O_WRONLY, 0644 );
	retval = gp_file_new_from_fd( &file, fd );
	//printf("  Retval: %d\n", retval);
	retval = gp_camera_file_get( camera, camera_file_path.folder, camera_file_path.name, GP_FILE_TYPE_NORMAL, file, context );
	//printf("  Retval: %d\n", retval);

	//printf("Deleting.\n");
	retval = gp_camera_file_delete( camera, camera_file_path.folder, camera_file_path.name, context );
	//printf("  Retval: %d\n", retval);

	gp_file_free( file );
        return fn;
}


static void errordumper( GPLogLevel level, const char *domain, const char *str, void *data )
{
	Gphoto* d = static_cast<Gphoto*>(data);
	if( d )
	{
		// to display class specific informations...
		// or save log errors...
	}
	std::cout << "-- Gphoto2 --" << std::endl;
	switch( level )
	{
		case GP_LOG_ERROR:
			std::cout << "Error" << std::endl;
			break;
		case GP_LOG_VERBOSE:
			std::cout << "Verbose" << std::endl;
			break;
		case GP_LOG_DEBUG:
			std::cout << "Debug" << std::endl;
			break;
		case GP_LOG_DATA:
			std::cout << "Data" << std::endl;
			break;
	}
	std::cout << "Domain: " << domain << std::endl;
	std::cout << "Message: " << str << std::endl;
	std::cout << "-------------------" << std::endl;
}

#endif

Gphoto::Gphoto()
{
        _cameraIsInit = 0/*false*/;
}

Gphoto::~Gphoto()
{
#ifdef WITH_GPHOTO2
	gp_camera_exit( _camera, _context );
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}


//bool Gphoto::getVarCameraIsInit() {
//    return /*_cameraIsInit*/0;
//}

void Gphoto::setVarCameraIsInit(bool var) {
    _cameraIsInit = var;
}


void Gphoto::initContext()
{
#ifdef WITH_GPHOTO2
        _context = sample_create_context();
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

int Gphoto::initCamera() {
#ifdef WITH_GPHOTO2
        initContext();
        //gp_log_add_func( GP_LOG_ERROR, errordumper, (void*)this );
        gp_camera_new( & _camera );
        int retval = gp_camera_init( _camera, _context );
        std::cout<<"RETVAL DE INIT CAMARA"<<retval<<std::endl;
        if( retval < GP_OK )
        {
            std::cout<<"NO CAMERA AUTO DETECTED"<<std::endl;
                //printf("No camera auto detected.\n");
                gp_camera_free( _camera );
                _cameraIsInit = 0/*false*/;
                return 0;
        }
        _cameraIsInit = 1/*true*/;
        return 1;
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

void Gphoto::getSummary()
{
#ifdef WITH_GPHOTO2
	CameraText text;
	int retval = gp_camera_get_summary( _camera, &text, _context );
	if( retval < GP_OK )
	{
		//printf("Camera failed retrieving summary.\n");
		gp_camera_free( _camera );
	}
	//printf("Summary:\n%s\n", text.text);
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

boost::filesystem::path Gphoto::captureToFile()
{
#ifdef WITH_GPHOTO2
        boost::filesystem::path fn = capture_to_file( _camera, _context, _fileName );
        return fn;
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

void Gphoto::doPreview(int i) {

//    int ret;
//    //i => define the number the stop condition
//            //printf("Taking 100 previews and saving them to snapshot-XXX.jpg ...\n");
//            int i;
//            while (flag == 1) {
    int ret;
                    CameraFile *file;

    //HAVE TO BE CHANGE IN FUNCTION OF CHOICE OF USERT PROJECT FILE//
                    char * outputFile;
                    boost::filesystem::path outputFilePath("projet/previewTps");
                    outputFile = (char*)outputFilePath.string().data();


                    fprintf(stderr,"preview %d\n", i);
                    ret = gp_file_new(&file);
                    if (ret != GP_OK) {
                            fprintf(stderr,"gp_file_new: %d\n", ret);
                            exit(1);
                    }
    #if 0 /* testcase for EOS zooming */
                    {
                            char buf[20];
                            if (i<10) set_config_value_string (_camera, "eoszoom", "5", _context);
                            sprintf(buf,"%d,%d",(i&0x1f)*64,(i>>5)*64);
                            fprintf(stderr, "%d - %s\n", i, buf);
                            set_config_value_string (_camera, "eoszoomposition", buf, _context);
                    }
    #endif
                    ret = gp_camera_capture_preview(_camera, file, _context);
                    if (ret != GP_OK) {
                            fprintf(stderr,"gp_camera_capture_preview(%d): %d\n", i, ret);
                            exit(1);
                    }

    //HAVE TO BE CHANGE IN FUNCTION OF CHOICE OF USERT PROJECT FILE//
                    sprintf(outputFile, "projet/previewTps/snapshot-%03d.jpg", i);
                    //std::cout<<"SAVE FILE IN : "<<outputFile<<std::endl;
                    ret = gp_file_save(file, outputFile);
                    if (ret != GP_OK) {
                            fprintf(stderr,"gp_camera_capture_preview(%d): %d\n", i, ret);
                            exit(1);
                    }
                    gp_file_unref(file);

                    //AFFICHIER IMAGE

                    boost::filesystem::path FileToDeletePath(outputFile);
                    boost::filesystem::remove(FileToDeletePath);

                    //know if we're still on the good image on the timeline

//                    ++i;
//            }
}

void Gphoto::exitCamera()
{
#ifdef WITH_GPHOTO2
	gp_camera_exit( _camera, _context );
        _cameraIsInit = 0/*false*/;
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

int Gphoto::tryToConnectCamera()
{
    std::cout<<"IS INIT?"<<_cameraIsInit<<std::endl;
	if( !_cameraIsInit )
	{
          //std::cout<<"CAMERAISIT à FALSE"<<std::endl;
               int isInit = initCamera();
                if (isInit == 0)
                {
                  return 0;
                }

	}
         //std::cout<<"CAMERAISIT à FALSE"<<std::endl;
        return 1;
}


//Settings of camera (canon)
void Gphoto::setShutterSpeed() {
//    canonShutterSpeedState shutter_speed = 0x5b;
//    canon_int_set_shutter_speed(_camera, shutter_speed, _context);
}
