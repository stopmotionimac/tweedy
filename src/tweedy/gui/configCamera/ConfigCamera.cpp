#include "ConfigCamera.hpp"

ConfigCamera::ConfigCamera(QWidget *parent) : QWidget(parent)
{
    Projet& projectInstance = Projet::getInstance();

    QScrollArea * scrollArea = new QScrollArea(this);

    /*Add as many layout as we have param on the camera*/

    int isConnected = projectInstance.tryToConnectCamera();
    if (isConnected == 0)
    {
        //Label for no camera connected
        QLabel * noCameraLabel = new QLabel(this);
        noCameraLabel->setMargin(30);
        noCameraLabel->setText("There is no camera detected");
        scrollArea->setWidget(noCameraLabel);
    }
    else
    {
        QVBoxLayout * layoutForListOfParam = new QVBoxLayout(this);

        QWidget * widgetForListOfParam = new QWidget(this);
        //Change size in fonction of config's number

        widgetForListOfParam->setLayout(layoutForListOfParam);

        //to get the widgets
        projectInstance.gPhotoInstance().findMainWidget();
        CameraWidget * mainWidget= projectInstance.gPhotoInstance().getMainWidget();
        projectInstance.gPhotoInstance().findChildrenOfOneWidget(mainWidget);
        std::vector<CameraWidget*>& widgetsVector = projectInstance.gPhotoInstance().getWidgetsVector();
        widgetForListOfParam->setFixedHeight(50*widgetsVector.size());

        for (int i = 0; i<widgetsVector.size(); ++i) {

            int type = projectInstance.gPhotoInstance().getTypeWidget(widgetsVector.at(i));

            //Label (What param)
            //Can evolve with Gphoto
            if (type == GP_WIDGET_RADIO  || type == GP_WIDGET_TEXT) {
                QWidget * widgetOfOneParam = new QWidget(this);
                layoutForListOfParam->addWidget(widgetOfOneParam);
                QHBoxLayout * layoutForOneParam = new QHBoxLayout(this);
                widgetOfOneParam->setLayout(layoutForOneParam);

                QLabel * labelParam = new QLabel(this);
                labelParam->setText(QString::fromStdString(projectInstance.gPhotoInstance().getNameOfAWidget(widgetsVector.at(i))));
                layoutForOneParam->addWidget(labelParam);

                switch( type )
                {
                    case GP_WIDGET_RADIO:
                    {
                        /*NPO RECUPERER LA VALEUR PAR DEFAULT*/

                        GPhotoWidgetTextItems * textItems = new GPhotoWidgetTextItems( widgetsVector.at(i)/*, this*/);
                        /*make the menu*/
                        QComboBox * listChoice = textItems->makeMenu();
                        layoutForOneParam->addWidget(listChoice);
                        textItems->putChoicesIntoMenu();
                        break;
                    }

                    // CASE TOGGLE DON'T REALLY WORK WITH QPHOTO (don't keep the value) //
    //                case GP_WIDGET_TOGGLE:
    //                {
    //                /*NPO RECUPERER LA VALEUR PAR DEFAULT*/
    //                    GPhotoWidgetToggle * yes = new GPhotoWidgetToggle( widgetsVector.at(i)/*, this*/);
    //                    GPhotoWidgetToggle * no = new GPhotoWidgetToggle( widgetsVector.at(i)/*, this*/);
    //                    /*make the menu*/
    //                    QRadioButton * toggleYes = yes->makeButton("yes");
    //                    QRadioButton * toggleNo = no->makeButton("no");
    //                    layoutForOneParam->addWidget(toggleYes);
    //                    layoutForOneParam->addWidget(toggleNo);
    //                    break;
    //                }

                    case GP_WIDGET_TEXT:
                    {
                        GPhotoWidgetTextField * textField = new GPhotoWidgetTextField( widgetsVector.at(i)/*, this*/);

                        QLineEdit * text = textField->makeMenu();
                        layoutForOneParam->addWidget(text);
                        break;
                    }
                }
            }
        }
        scrollArea->setWidget(widgetForListOfParam);
    }

    QVBoxLayout * layoutForScrollArea = new QVBoxLayout(this);
    layoutForScrollArea->addWidget(scrollArea);
}
