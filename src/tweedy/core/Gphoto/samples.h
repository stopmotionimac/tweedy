#ifndef __SAMPLES_H
#define __SAMPLES_H

#include <gphoto2/gphoto2-camera.h>
#include<gphoto2/gphoto2-context.h>

int sample_autodetect (CameraList *list, GPContext *context);
int sample_open_camera (Camera ** camera, const char *model, const char *port);
GPContext* sample_create_context(void);

int get_config_value_string (Camera *, const char *, char **, GPContext *);
int set_config_value_string (Camera *, const char *, const char *, GPContext *);
int canon_enable_capture (Camera *camera, int onoff, GPContext *context);

#endif
