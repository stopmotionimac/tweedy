#include <gphoto2/gphoto2.h>

#include <iostream>
#include <cstdlib>

int main (int argc, char** argv)
{
      GPContext *currentContext = NULL;
      gp_context_new();

      Camera *camera=NULL;
      gp_camera_new (&camera);
      CameraAbilitiesList * abilitiesList = NULL;
      CameraAbilities  abilities;
      CameraAbilities * ptr_abilities;
      ptr_abilities = &abilities;
      int haveListAbilities = gp_abilities_list_get_abilities (abilitiesList, 0, ptr_abilities);
      int haveAbilities = gp_camera_set_abilities(camera, abilities);

/*      //in case camera driver can't figure out the current camera's speed
      //gp_camera_set_port_path or name => pas TROUVE
      int speed; //AURA BESOIN D4UNE VALEUR (???)
      int hasSpeed = gp_camera_set_port_speed (camera, speed);
*/

      gp_camera_init (camera, currentContext);

      //to know port's camera
      GPPortInfo info;
      GPPortInfo * ptr_info;
      ptr_info = &info;
      int infoSetted = gp_camera_set_port_info (camera, info);


      ///
      int infoGetted = gp_camera_get_port_info(camera, ptr_info);


      //To have a window with camera's config
      CameraWidget ** widget;
      CameraWidgetType type;
      const char *label;
      int widgetCreated = gp_widget_new (type, label, widget);
      int configGetted = gp_camera_get_config (camera, widget, currentContext);

      int indiceCountCamera = gp_camera_unref (camera);

        //Before the end of using camera => better!
        int cameraExited = gp_camera_exit (camera, currentContext);
        return EXIT_SUCCESS;
}
