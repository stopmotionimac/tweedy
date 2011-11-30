#include <gphoto2/gphoto2.h>

#include <iostream>
#include <cstdlib>

int main (int argc, char** argv)
{

//std::cout<<*cameraUsed<<std::endl;

    //Camera ** cameraUsed;

   // int (*pointeurFonctionCameraNew)(**Camera);
   //pointeurFonctionCameraNew = gp_camera_new;

//    int a;
//    a = gp_camera_new(cameraUsed);
    //a = (*pointeurFonctionCameraNew)(cameraUsed);

    //GPContext* currentContext;
    //  GPContext* gp_context_new();


    //int initCamera;
    //initCamera = camera_init(cameraUsed, GPContext);



 /*   Camera * cameraUsed;
    int returnCameraNew;
    returnCameraNew = gp_camera_new(&cameraUsed);

 */

/*    Camera * canon;
      int i, retval;
      GPContext * canoncontext = gp_context_new();
      gp_camera_new(&canon);
*/

      Camera *camera=NULL;
      gp_camera_new (&camera);
      gp_camera_init (camera, NULL);
      gp_camera_unref (camera);


        return EXIT_SUCCESS;
}
