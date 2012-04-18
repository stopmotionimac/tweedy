#include "Gphoto.hpp"


Gphoto::Gphoto()
{
        _cameraIsInit = 0/*false*/;
}

Gphoto::~Gphoto()
{
#ifdef WITH_GPHOTO2
        gp_camera_exit( _camera, _context );
        int ret = gp_widget_free(_mainWidget);
        ret = gp_widget_unref(_mainWidget);

        for(int i = 0; i<_WidgetsVector.size(); ++i)
        {
            ret = gp_widget_free(_WidgetsVector.at(i));
            ret = gp_widget_unref(_WidgetsVector.at(i));
        }

        _WidgetsVector.clear();


#else
        std::cout << "Error: Not compiled with gphoto2." << std::endl;
#endif
}

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



        //For raw format
            //SI ON PREND LE RAW, IL NE PEUT PAS PRENDRE LE JPG, MEME SI ON EST EN DOUBLE MODE
            //LE RAW POSE SOUCIS DANS TWEEDY A L'AFFICHAGE (EN PLUS EST LOURD) (.CR2)
//        std::string fnTpsString = fn.string();

//        fnTpsString.insert( fnTpsString.size() - 4, "_RAW" );

//        const char * fnToOpenRaw = fnTpsString.data();
//        std::cout << fnToOpenRaw << std::endl;

//        //folder/file on computer
//        fd = open( fnToOpenRaw, O_CREAT | O_WRONLY, 0644 );
//        retval = gp_file_new_from_fd( &file, fd );
//        //printf("  Retval: %d\n", retval);

        //retval = gp_camera_file_get( camera, camera_file_path.folder, camera_file_path.name, GP_FILE_TYPE_RAW, file, context );

        //retval = gp_camera_file_get( camera, camera_file_path.folder, camera_file_path.name, GP_FILE_TYPE_PREVIEW, file, context );

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
        if( retval < GP_OK )
        {
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

std::string Gphoto::doPreview(int i) {

    int ret;
                    CameraFile *file;

                    char * outputFile;
                    //boost::filesystem::path outputFilePath("/home/solvejg/Bureau/projet/pictures/");
                    boost::filesystem::path outputFilePath = _fileName ;
                    outputFile = (char*)outputFilePath.string().data();


                    //fprintf(stderr,"preview %d\n", i);
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

                    sprintf(outputFile, "snapshot-%03d.jpg", i);
                    ret = gp_file_save(file, outputFile);
                    if (ret != GP_OK) {
                            fprintf(stderr,"gp_camera_capture_preview(%d): %d\n", i, ret);
                            exit(1);
                    }
                    gp_file_unref(file);
                    return outputFile;
}

void Gphoto::findMainWidget() {
    const char* nameMainWidget = NULL;
    const char* labelMainWidget = NULL;

    int ret;

    ret = gp_widget_new (GP_WIDGET_MENU, "WINDOW 01", &_mainWidget);

    ret = gp_camera_get_config(_camera, &_mainWidget, _context);
    ret = gp_widget_get_name (_mainWidget, &nameMainWidget);
    ret = gp_widget_get_label (_mainWidget, &labelMainWidget);
//    int countChildren = gp_widget_count_children (_mainWidget);
}

void Gphoto::findChildrenOfOneWidget(CameraWidget* parentWidget) {
    CameraWidget * child;
    int idChild;
//    const char* name;

    int ret;

    int countChildren = gp_widget_count_children (parentWidget);

    for (int i = 0; i< countChildren; ++i)
    {
         ret = gp_widget_get_child (parentWidget, i, &child);
//OK

         int countChildrenOfChildren = gp_widget_count_children (child);

         if (countChildrenOfChildren != 0)
         {
             findChildrenOfOneWidget(child);
         }
         else {
             //put children on the vector
             _WidgetsVector.push_back(child);
         }
     }
}

std::string Gphoto::getNameOfAWidget(CameraWidget *widget) {
    const char* name;
    int ret = gp_widget_get_name (widget, &name);
    return name;

}

bool Gphoto::isRadioOrMenu(CameraWidget *widget) {
    //CameraWidgetType *type;
    //int ret = gp_widget_count_choices(widget);
    int ret = CountChoices(widget);
    if (ret > 0) {
        return true;
    }
    else {
        return false;
    }
}

int Gphoto::CountChoices(CameraWidget *widget) {
    int ret = gp_widget_count_choices(widget);
    return ret;
}

std::string Gphoto::getChoice(CameraWidget *widget, int choiceNumber) {
    const char * choice;
    int ret = gp_widget_get_choice (widget, choiceNumber, &choice);
    std::string choiceS(choice);
    return choiceS;

}

int Gphoto::getTypeWidget(CameraWidget *widget) {
    CameraWidgetType type;
    int ret = gp_widget_get_type (widget, &type);
    return type;
}

int Gphoto::_lookup_widget(CameraWidget*widget, const char *key, CameraWidget **child) {
        int ret;
        ret = gp_widget_get_child_by_name (widget, key, child);
        if (ret < GP_OK)
                ret = gp_widget_get_child_by_label (widget, key, child);
        return ret;
}
/*Works for int*/
void Gphoto::getValue(CameraWidget *widget) {
    int value;
    int ret = get_config_value (_camera, getNameOfAWidget(widget).data(), &value, _context);
}

int Gphoto::get_config_value (Camera *camera, const char *key, int * str, GPContext *context){
    CameraWidget		*widget = NULL, *child = NULL;
    CameraWidgetType	type;
    int			ret;
    int			val;

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
    case GP_WIDGET_TOGGLE:
            break;
    default:
            fprintf (stderr, "widget has bad type %d\n", type);
            ret = GP_ERROR_BAD_PARAMETERS;
            goto out;
    }

    /* This is the actual query call. Note that we just
     * a pointer reference to the string, not a copy... */
    ret = gp_widget_get_value (child, &val);
    if (ret < GP_OK) {
            fprintf (stderr, "could not query widget value: %d\n", ret);
            goto out;
    }
    /* Create a new copy for our caller. */
    *str = val;
out:
    gp_widget_free (widget);
    return ret;
}

int Gphoto::get_config_value (Camera *camera, const char *key, char ** str, GPContext *context) {
        CameraWidget		*widget = NULL, *child = NULL;
        CameraWidgetType	type;
        int			ret;
        char			*val;

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
        //case GP_WIDGET_TOGGLE:
                break;
        default:
                fprintf (stderr, "widget has bad type %d\n", type);
                ret = GP_ERROR_BAD_PARAMETERS;
                goto out;
        }

        /* This is the actual query call. Note that we just
         * a pointer reference to the string, not a copy... */
        ret = gp_widget_get_value (child, &val);
        if (ret < GP_OK) {
                fprintf (stderr, "could not query widget value: %d\n", ret);
                goto out;
        }
        /* Create a new copy for our caller. */
        *str = strdup(val);
out:
        gp_widget_free (widget);
        return ret;
}

void Gphoto::setValueString(CameraWidget *widget, const void *value){
    int ret = set_config_value (_camera, getNameOfAWidget(widget).data(), value, _context);
}

void Gphoto::setValueInt(CameraWidget *widget, /*const void **/ int value){
    int * val = &value;
    int ret = set_config_value(_camera, getNameOfAWidget(widget).data(), val, _context);
}

int Gphoto::set_config_value (Camera *camera, const char *key, const void * val, GPContext *context) {
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
        case GP_WIDGET_TOGGLE:
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
	if( !_cameraIsInit )
	{
               int isInit = initCamera();
                if (isInit == 0)
                {
                  return 0;
                }
	}
        return 1;
}
