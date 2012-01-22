#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <string>
#include <boost/filesystem.hpp>
#include <gphoto2/gphoto2.h>
#include "samples.h"

static void errordumper(GPLogLevel level, const char *domain, const char *str,
                 void *data) {
  fprintf(stdout, "%s\n", str);
}

static void
capture_to_memory(Camera *camera, GPContext *context, const char **ptr, unsigned long int *size) {
	int retval;
	CameraFile *file;
	CameraFilePath camera_file_path;

	printf("Capturing.\n");

	/* NOP: This gets overridden in the library to /capt0000.jpg */
	strcpy(camera_file_path.folder, "/");
	strcpy(camera_file_path.name, "foo.jpg");

	retval = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &camera_file_path, context);
	printf("  Retval: %d\n", retval);

	printf("Pathname on the camera: %s/%s\n", camera_file_path.folder, camera_file_path.name);

	retval = gp_file_new(&file);
	printf("  Retval: %d\n", retval);
	retval = gp_camera_file_get(camera, camera_file_path.folder, camera_file_path.name,
		     GP_FILE_TYPE_NORMAL, file, context);
	printf("  Retval: %d\n", retval);

	gp_file_get_data_and_size (file, ptr, size);

	printf("Deleting.\n");
	retval = gp_camera_file_delete(camera, camera_file_path.folder, camera_file_path.name,
			context);
	printf("  Retval: %d\n", retval);

	gp_file_free(file);
}

static void
        capture_to_file(Camera *camera, GPContext *context, boost::filesystem::path & fn /*const char * fn*/) {
	int fd, retval;
	CameraFile *file;
	CameraFilePath camera_file_path;

	printf("Capturing.\n");
	
	/* NOP: This gets overridden in the library to /capt0000.jpg */
	strcpy(camera_file_path.folder, "/");
        strcpy(camera_file_path.name, "foo.jpg");

	retval = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &camera_file_path, context);
	printf("  Retval: %d\n", retval);

	printf("Pathname on the camera: %s/%s\n", camera_file_path.folder, camera_file_path.name);

	/*OK si on est dans tweedy!*/
        fn /= camera_file_path.name;
        const char * fnToOpen = fn.string().data();
        std::cout<<fnToOpen<<std::endl;

        //folder/file on computer
        fd = open(fnToOpen, O_CREAT | O_WRONLY, 0644);
        retval = gp_file_new_from_fd(&file, fd);
	printf("  Retval: %d\n", retval);
        retval = gp_camera_file_get(camera, camera_file_path.folder, camera_file_path.name, GP_FILE_TYPE_NORMAL, file, context);
	printf("  Retval: %d\n", retval);

	printf("Deleting.\n");
        retval = gp_camera_file_delete(camera, camera_file_path.folder, camera_file_path.name,context);
        printf("  Retval: %d\n", retval);

	gp_file_free(file);
}

int
main(int argc, char **argv) {
	Camera	*camera;
	int	retval;
	GPContext *context = sample_create_context();

        //
	const char ** ptr;
	unsigned long int *  size;
        //const char * fileName;

        boost::filesystem::path fileName( "sandbox/testGPhoto/pictures/" );

	gp_log_add_func(GP_LOG_ERROR, errordumper, NULL);
	gp_camera_new(&camera);

        printf("Camera init.\n");
	retval = gp_camera_init(camera, context);
	if (retval != GP_OK) {
		printf("  Retval: %d\n", retval);
		exit (1);
	}
        //Change the Speed (TEST)
        //canonShutterSpeedState shutter_speed = SHUTTER_SPEED_1_20;
        //canon_int_set_shutter_speed(camera, shutter_speed, context);

        //retval = canon_int_ready(camera, context);

	//capture_to_file(Camera *camera, GPContext *context, char *fn) 
        capture_to_file(camera, context, fileName);
	//capture_to_memory(camera, context, ptr, size);
	gp_camera_exit(camera, context);
	return 0;
}
