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

static int
_lookup_widget(CameraWidget*widget, const char *key, CameraWidget **child) {
        int ret;
        ret = gp_widget_get_child_by_name (widget, key, child);
        if (ret < GP_OK)
                ret = gp_widget_get_child_by_label (widget, key, child);
        return ret;
}

/* Gets a string configuration value.
 * This can be:
 *  - A Text widget
 *  - The current selection of a Radio Button choice
 *  - The current selection of a Menu choice
 *
 * Sample (for Canons eg):
 *   get_config_value_string (camera, "owner", &ownerstr, context);
 */
int
get_config_value_string (Camera *camera, const char *key, char **str, GPContext *context) {
        CameraWidget		*widget = NULL, *child = NULL;
        CameraWidgetType	type;
        int			ret;
        //char			*val;

        ret = gp_camera_get_config (camera, &widget, context);
        if (ret < GP_OK) {
                fprintf (stderr, "camera_get_config failed: %d\n", ret);
                return ret;
        }
        ret = _lookup_widget (widget, key, &child);
        if (ret < GP_OK) {
                fprintf (stderr, "lookup widget failed: %d\n", ret);
                goto out;
        }

        /* This type check is optional, if you know what type the label
         * has already. If you are not sure, better check. */
        ret = gp_widget_get_type (child, &type);
        if (ret < GP_OK) {
                fprintf (stderr, "widget get type failed: %d\n", ret);
                goto out;
        }
//        switch (type) {
//        case GP_WIDGET_MENU:
//        case GP_WIDGET_RADIO:
//        case GP_WIDGET_TEXT:
//                break;
//        default:
//                fprintf (stderr, "widget has bad type %d\n", type);
//                ret = GP_ERROR_BAD_PARAMETERS;
//                goto out;
//        }
        std::cout<<"AVT GET_VALUE"<<std::endl;
        int val;

        /* This is the actual query call. Note that we just
         * a pointer reference to the string, not a copy... */
        ret = gp_widget_get_value (child, &val);
        if (ret < GP_OK) {
                fprintf (stderr, "could not query widget value: %d\n", ret);
                goto out;
        }
        std::cout<<"APRES GET_VALUE"<<std::endl;
        std::cout<<val<<std::endl;
        /* Create a new copy for our caller. */
        //*str = strdup (val);
out:
        gp_widget_free (widget);
        return ret;
}


/* Sets a string configuration value.
 * This can set for:
 *  - A Text widget
 *  - The current selection of a Radio Button choice
 *  - The current selection of a Menu choice
 *
 * Sample (for Canons eg):
 *   get_config_value_string (camera, "owner", &ownerstr, context);
 */
int
set_config_value_string (Camera *camera, const char *key, const char *val, GPContext *context) {
        CameraWidget		*widget = NULL, *child = NULL;
        CameraWidgetType	type;
        int			ret;

        ret = gp_camera_get_config (camera, &widget, context);
        if (ret < GP_OK) {
                fprintf (stderr, "camera_get_config failed: %d\n", ret);
                return ret;
        }
        ret = _lookup_widget (widget, key, &child);
        if (ret < GP_OK) {
                fprintf (stderr, "lookup widget failed: %d\n", ret);
                goto out;
        }

        /* This type check is optional, if you know what type the label
         * has already. If you are not sure, better check. */
        ret = gp_widget_get_type (child, &type);
        if (ret < GP_OK) {
                fprintf (stderr, "widget get type failed: %d\n", ret);
                goto out;
        }
        switch (type) {
        case GP_WIDGET_MENU:
        case GP_WIDGET_RADIO:
        case GP_WIDGET_TEXT:
                break;
        default:
                fprintf (stderr, "widget has bad type %d\n", type);
                ret = GP_ERROR_BAD_PARAMETERS;
                goto out;
        }

        /* This is the actual set call. Note that we keep
         * ownership of the string and have to free it if necessary.
         */
        ret = gp_widget_set_value (child, val);
        if (ret < GP_OK) {
                fprintf (stderr, "could not set widget value: %d\n", ret);
                goto out;
        }
        /* This stores it on the camera again */
        ret = gp_camera_set_config (camera, widget, context);
        if (ret < GP_OK) {
                fprintf (stderr, "camera_set_config failed: %d\n", ret);
                return ret;
        }
out:
        gp_widget_free (widget);
        return ret;
}


/*
 * This enables/disables the specific canon capture mode.
 *
 * For non canons this is not required, and will just return
 * with an error (but without negative effects).
 */
int
canon_enable_capture (Camera *camera, int onoff, GPContext *context) {
        CameraWidget		*widget = NULL, *child = NULL;
        CameraWidgetType	type;
        int			ret;

        ret = gp_camera_get_config (camera, &widget, context);
        if (ret < GP_OK) {
                fprintf (stderr, "camera_get_config failed: %d\n", ret);
                return ret;
        }
        ret = _lookup_widget (widget, "capture", &child);
        if (ret < GP_OK) {
                /*fprintf (stderr, "lookup widget failed: %d\n", ret);*/
                goto out;
        }

        ret = gp_widget_get_type (child, &type);
        if (ret < GP_OK) {
                fprintf (stderr, "widget get type failed: %d\n", ret);
                goto out;
        }
        switch (type) {
        case GP_WIDGET_TOGGLE:
                break;
        default:
                fprintf (stderr, "widget has bad type %d\n", type);
                ret = GP_ERROR_BAD_PARAMETERS;
                goto out;
        }
        /* Now set the toggle to the wanted value */
        ret = gp_widget_set_value (child, &onoff);
        if (ret < GP_OK) {
                fprintf (stderr, "toggling Canon capture to %d failed with %d\n", onoff, ret);
                goto out;
        }
        /* OK */
        ret = gp_camera_set_config (camera, widget, context);
        if (ret < GP_OK) {
                fprintf (stderr, "camera_set_config failed: %d\n", ret);
                return ret;
        }
out:
        gp_widget_free (widget);
        return ret;
}

int main(int argc, char **argv) {
        Camera		*camera;
        int		ret;
        char		*owner;
        GPContext	*context;

        context = sample_create_context (); /* see context.c */
        gp_camera_new (&camera);

        /* This call will autodetect cameras, take the
         * first one from the list and use it. It will ignore
         * any others... See the *multi* examples on how to
         * detect and use more than the first one.
         */
        ret = gp_camera_init (camera, context);
        if (ret < GP_OK) {
                printf("No camera auto detected.\n");
                gp_camera_free (camera);
                return 0;
        }

        canon_enable_capture(camera, TRUE, context);
        /*set_capturetarget(canon, canoncontext);*/



        //PREVIEW
////i => define the number the stop condition
//        //printf("Taking 100 previews and saving them to snapshot-XXX.jpg ...\n");
//        int i;
//        while (i < 10) {
//                CameraFile *file;
//
////HAVE TO BE CHANGE IN FUNCTION OF CHOICE OF USERT PROJECT FILE//
//                char * outputFile;
//                boost::filesystem::path outputFilePath("projet/previewTps");
//                outputFile = (char*)outputFilePath.string().data();
//
//
//                fprintf(stderr,"preview %d\n", i);
//                ret = gp_file_new(&file);
//                if (ret != GP_OK) {
//                        fprintf(stderr,"gp_file_new: %d\n", ret);
//                        exit(1);
//                }
//#if 0 /* testcase for EOS zooming */
//                {
//                        char buf[20];
//                        if (i<10) set_config_value_string (camera, "eoszoom", "5", context);
//                        sprintf(buf,"%d,%d",(i&0x1f)*64,(i>>5)*64);
//                        fprintf(stderr, "%d - %s\n", i, buf);
//                        set_config_value_string (camera, "eoszoomposition", buf, context);
//                }
//#endif
//                ret = gp_camera_capture_preview(camera, file, context);
//                if (ret != GP_OK) {
//                        fprintf(stderr,"gp_camera_capture_preview(%d): %d\n", i, ret);
//                        exit(1);
//                }
//
////HAVE TO BE CHANGE IN FUNCTION OF CHOICE OF USER PROJECT FILE//
//                sprintf(outputFile, "projet/previewTps/snapshot-%03d.jpg", i);
//                //std::cout<<"SAVE FILE IN : "<<outputFile<<std::endl;
//                ret = gp_file_save(file, outputFile);
//                if (ret != GP_OK) {
//                        fprintf(stderr,"gp_camera_capture_preview(%d): %d\n", i, ret);
//                        exit(1);
//                }
//                gp_file_unref(file);
//
//                //AFFICHIER IMAGE
//
//                boost::filesystem::path FileToDeletePath(outputFile);
//                boost::filesystem::remove(FileToDeletePath);
//                ++i;
//        }
        //END PREVIEW

        //GET AND SET CONFIG TOGGLE
        char * val;
        ret = get_config_value_string(camera, "bulb", &val, context);
        std::cout<<"RET : "<<ret<<std::endl;
        std::cout<<"VAL RETURNED : "<<val<<std::endl;
        //ENDOF GET AND SET CONFIG TOGGLE

        /*to set camera config we have to know tha camera owner*/
        /*Get the camera owner . if there is no owner set a default one*/
        ret = get_config_value_string (camera, "ownername", &owner, context);
        if (ret < GP_OK)
        {
            printf ("No owner.\n");
            //goto out;
            ret = set_config_value_string (camera, "ownername", "DefaultOwner", context);
            if (ret < GP_OK) {
                fprintf (stderr, "Failed to set camera owner to \"DefaultOwner\"; %d\n", ret);
            } else { printf("New owner: %s\n", owner); }
        }
        else
        {
            std::cout<<owner<<std::endl;



            /*to abilities*/
            CameraAbilitiesList * abilitiesList;
            CameraAbilitiesList ** ptr_abilitiesList;
            ptr_abilitiesList = &abilitiesList;
            CameraAbilities  abilities;
            CameraAbilities * ptr_abilities;
            ptr_abilities = &abilities;

            //VOIR ACTION.C LIGNE 838


            /*to init the list of abiolities*/
            int ret = gp_abilities_list_new (ptr_abilitiesList);
            ret = gp_abilities_list_load (abilitiesList, context);

            /*to get abilities*/

            /*get number of abilities => NB APPAREILS :'(*/
            int nbAbilities = gp_abilities_list_count (abilitiesList);
            std::cout<<"NB ABILITIES : "<<nbAbilities<<std::endl;

            int haveListAbilities = gp_abilities_list_get_abilities (abilitiesList, 0, ptr_abilities);
            std::cout<<"haveListAbilities : "<< haveListAbilities<<std::endl;

//            int haveAbilities = gp_camera_set_abilities(camera, abilities);
//            std::cout<<"haveAbilities : "<< haveAbilities<<std::endl;
//
//            //in case camera driver can't figure out the current camera's speed
//            //gp_camera_set_port_path or name => pas TROUVE
//            int speed; //AURA BESOIN D'UNE VALEUR (???)
//            int hasSpeed = gp_camera_set_port_speed (camera, speed);

            /*FOR WIDGET*/
            CameraWidget * window;
            CameraWidget ** ptr_window;
            ptr_window = &window;
            const char* nameWindow = NULL;
            const char* labelWindow = NULL;

            ret = gp_widget_new (GP_WIDGET_MENU/*GP_WIDGET_WINDOW*/, "WINDOW 01", ptr_window);
            int id;


            ret = gp_camera_get_config(camera, ptr_window, context);
        //    std::cout<<"RETURN OF GET CONFIG: "<<ret<<std::endl;
            ret = gp_widget_get_id (window, &id);
            std::cout<<"ID DE LA WIDGET : "<<id<<std::endl;
            ret = gp_widget_get_name (window, &nameWindow);
            std::cout<<"NAME DE LA WIDGET : "<<nameWindow<<std::endl;
            ret = gp_widget_get_label (window, &labelWindow);
            std::cout<<"LABEL DE LA WIDGET : "<<labelWindow<<std::endl;
            //int countChoice = gp_widget_count_choices (window);
            int countChildren = gp_widget_count_children (window);
            std::cout<<"NB OF CHILDREN : "<<countChildren<<std::endl;


            CameraWidget * child;
            CameraWidget ** ptr_child;
            ptr_child = &child;
            int idChild;
            const char* name;

//SI LES AUTRES MODELES SONT CLASSES DIFFEREMENT, VOIR POUR FAIRE UN WHILE QUI CONTIENT LE FOR
            for (int i = 0; i< countChildren; ++i)
            {
                 /*Children level 1*/

                 ret = gp_widget_get_child (window, i, ptr_child);
                 std::cout<<"RET GET CHILD : "<<ret<<std::endl;
                 //ret = gp_widget_get_id (child, &idChild);
                 //std::cout<<"CHILD"<<i<<" ID : "<<id<<std::endl;
                 //ret = gp_widget_get_child_by_id (window, idChild, ptr_child);
                 //std::cout<<"RET GET CHILD BY ID : "<<ret<<std::endl;
                 ret = gp_widget_get_name (child, &name);
                 std::cout<<"NAME CHILDREN NIVEAU 1 ("<<i<<") : "<<name<<std::endl;

                 int countChildrenOfChildren = gp_widget_count_children (child);
                 std::cout<<"NB OF CHILDREN OF CHILDREN : "<<countChildrenOfChildren<<std::endl;

                 if (countChildrenOfChildren != 0)
                 {
                     CameraWidget * childOfChild;
                     CameraWidget ** ptr_childOfChild;
                     ptr_childOfChild = &childOfChild;
                     int idChildOfChild;
                     const char* nameOfChild;

                     for (int j = 0; j <= countChildrenOfChildren; ++j)
                     {
                         /*Children level 2*/

                         ret = gp_widget_get_child (child, j, ptr_childOfChild);
                         std::cout<<"RET GET CHILD : "<<ret<<std::endl;
                         ret = gp_widget_get_name (childOfChild, &nameOfChild);
                         std::cout<<"NAME CHILDREN NIVEAU 2 ("<<j<<") : "<<nameOfChild<<std::endl;

                         int countChildrenOfChildrenOfChildren = gp_widget_count_children (childOfChild);
                         std::cout<<"NB OF CHILDREN OF CHILDREN : "<<countChildrenOfChildrenOfChildren<<std::endl;
                         if (countChildrenOfChildrenOfChildren == 0)
                         {
                             std::cout<<"No Children"<<std::endl;
                         }
                     }
                 }
                 else
                 {
                     std::cout<<"No Children"<<std::endl;
                 }

             }

            /*
            to config ONE config
            //get_config_value_string (Camera *camera, const char *key, char **str, GPContext *context)
            */
            /*ISO*/
            //char * isoValue;
            //get_config_value_string (camera, "iso", &isoValue, context);


        }
out:
        gp_camera_exit (camera, context);
        gp_camera_free (camera);
        return 0;

    }
