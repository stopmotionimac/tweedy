#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <gphoto2/gphoto2-camera.h>

#include "samples.h"

/* Sample autodetection program.
 *
 * This program can autodetect multiple cameras and then calls a
 * simple function in each of them (summary).
 */

int main(int argc, char **argv)
{
        CameraList	*list;
        Camera		**cams;
        int		ret, i, count;
        const char	*name, *value;
        GPContext	*context;

        context = sample_create_context (); /* see context.c */

        /* Detect all the cameras that can be autodetected... */
        ret = gp_list_new (&list);
        if (ret < GP_OK) return 1;
        count = sample_autodetect (list, context);

        /* Now open all cameras we autodected for usage */
        printf("Number of cameras: %d\n", count);
        std::cout << __LINE__ << std::endl;
        cams = (Camera**)calloc (sizeof (Camera*),count);
        for (i = 0; i < count; i++)
        {
            std::cout << __LINE__ << std::endl;
                gp_list_get_name  (list, i, &name);
                std::cout << __LINE__ << std::endl;
                gp_list_get_value (list, i, &value);
                std::cout << __LINE__ << std::endl;
                ret = sample_open_camera (&cams[i], name, value);
                std::cout << __LINE__ << std::endl;
                if (ret < GP_OK) fprintf(stderr,"Camera %s on port %s failed to open\n", name, value);
                else fprintf(stdout,"Camera %s on port %s OK", name, value);
                std::cout << __LINE__ << std::endl;
        }

        std::cout << __LINE__ << std::endl;

        /* Now call a simple function in each of those cameras. */
        for (i = 0; i < count; i++)
        {
            std::cout << __LINE__ << std::endl;
                CameraText	text;
                char 		*owner;
                ret = gp_camera_get_summary (cams[i], &text, context);
                /*
                if(ret < GP_OK)
                {
                        fprintf (stderr, "Failed to get summary.\n");
                        continue;
                }*/

                std::cout << __LINE__ << std::endl;
                gp_list_get_name  (list, i, &name);
                gp_list_get_value (list, i, &value);
                printf("%-30s %-16s\n", name, value);
                printf("Summary:\n%s\n", text.text);

                /* Query a simple string configuration variable. */
                ret = get_config_value_string (cams[i], "owner", &owner, context);
                if (ret >= GP_OK) {
                        printf("Owner: %s\n", owner);
                        free (owner);
                } else {
                        printf("Owner: No owner found.\n");
                }
                std::cout << __LINE__ << std::endl;
        }
        std::cout << __LINE__ << std::endl;
        return 0;
}

#if 0

#include <gphoto2/gphoto2.h>

#include <iostream>
#include <cstdlib>

int main (int argc, char** argv)
{
      std::cout<<"GP_OK = "<<GP_OK<<std::endl;

      GPContext *currentContext = NULL;
      gp_context_new();

      Camera *camera=NULL;
      gp_camera_new (&camera);
      gp_camera_init (camera, currentContext);

      CameraAbilitiesList * abilitiesList;
      CameraAbilities  abilities;
      CameraAbilities * ptr_abilities;
      ptr_abilities = &abilities;
      int haveListAbilities = gp_abilities_list_get_abilities (abilitiesList, 0, ptr_abilities);
      std::cout<<"haveListAbilities : "<< haveListAbilities<<std::endl;

     /* int haveAbilities = gp_camera_set_abilities(camera, abilities);
      std::cout<<"haveAbilities : "<< haveAbilities<<std::endl;*/

/*      //in case camera driver can't figure out the current camera's speed
      //gp_camera_set_port_path or name => pas TROUVE
      int speed; //AURA BESOIN D4UNE VALEUR (???)
      int hasSpeed = gp_camera_set_port_speed (camera, speed);
*/



      //to know port's camera
      GPPortInfo info;
      GPPortInfo * ptr_info;
      ptr_info = &info;
     /* int infoSetted = gp_camera_set_port_info (camera, info);
      std::cout<<"infoSetted : "<< infoSetted<<std::endl;*/


      ///
      int infoGetted = gp_camera_get_port_info(camera, ptr_info);
      std::cout<<"infoGetted : "<< infoGetted<<std::endl;


      //To have a window with camera's config
      CameraWidget ** widget;
      CameraWidgetType type;
      const char *label;
      int widgetCreated = gp_widget_new (type, label, widget);
      std::cout<<"widgetCreated : "<< widgetCreated<<std::endl;

      //get config
      int configGetted = gp_camera_get_config (camera, widget, currentContext);
      std::cout<<"configGetted : "<< configGetted<<std::endl;

      //set the configuration's camera
//      int cameraSetted = gp_camera_set_config (camera, *widget, currentContext);
//      std::cout<<"cameraSetted : "<< cameraSetted<<std::endl;


      //HAVE TO FIND FUNCTION WHICH GET/SET THE PÄTH
      CameraFilePath * path;
      //IDEM
      CameraCaptureType typeCapture;
      CameraFileType typeFile; //mm type à priori
      //capture
      int captured = gp_camera_capture (camera, typeCapture, path, currentContext);
      std::cout<<"captured : "<< captured<<std::endl;

      //To get capture from camera to computer
      //folder on computer
      //TO COMPLETE
      const char *folder = "../pictures";
      //TO COMPLETE
      //(devra être renseigné en fonction du numéro de la photoprécédente par ex)
      const char *file = "picture001";

      //??
      CameraFile * camera_file;
      int captureGetted = gp_camera_file_get(camera, folder, file, typeFile,camera_file, currentContext);
      std::cout<<"captureGetted : "<< captureGetted<<std::endl;


      int indiceCountCamera = gp_camera_unref (camera);



        //Before the end of using camera => better!
        int cameraExited = gp_camera_exit (camera, currentContext);

        return EXIT_SUCCESS;
}
#endif
