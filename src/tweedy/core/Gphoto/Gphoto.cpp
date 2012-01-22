#include "Gphoto.hpp"

#ifdef WITH_GPHOTO2
#include "samples.h"
#include <gphoto2/gphoto2.h>
#include <gphoto2/gphoto2-port-log.h>
#endif

#include <iostream>

#ifdef WITH_GPHOTO2

static void capture_to_file( Camera *camera, GPContext *context, boost::filesystem::path & fn /*const char * fn*/ )
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
	_cameraIsInit = false;
}

Gphoto::~Gphoto()
{
#ifdef WITH_GPHOTO2
	gp_camera_exit( _camera, _context );
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

void Gphoto::initContext()
{
#ifdef WITH_GPHOTO2
	_context = sample_create_context();
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

void Gphoto::initCamera()
{
#ifdef WITH_GPHOTO2
	initContext();
//	gp_log_add_func( GP_LOG_ERROR, errordumper, (void*)this );
	gp_camera_new( & _camera );
	int retval = gp_camera_init( _camera, _context );
	if( retval < GP_OK )
	{
		//printf("No camera auto detected.\n");
		gp_camera_free( _camera );
	}
	_cameraIsInit = true;
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

void Gphoto::captureToFile()
{
#ifdef WITH_GPHOTO2
	capture_to_file( _camera, _context, _fileName );
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

void Gphoto::exitCamera()
{
#ifdef WITH_GPHOTO2
	gp_camera_exit( _camera, _context );
	_cameraIsInit = false;
#else
	std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

void Gphoto::tryToConnectCamera()
{
	if( !_cameraIsInit )
	{
		initCamera();
	}
}


//Settings of camera (canon)
void Gphoto::setShutterSpeed() {
//    canonShutterSpeedState shutter_speed = 0x5b;
//    canon_int_set_shutter_speed(_camera, shutter_speed, _context);
}
