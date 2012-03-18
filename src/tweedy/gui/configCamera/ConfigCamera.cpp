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
        //Change size in fonction of nuber of config

        widgetForListOfParam->setLayout(layoutForListOfParam);

        //to get the widgets
        projectInstance.gPhotoInstance().findMainWidget();
        CameraWidget * mainWidget= projectInstance.gPhotoInstance().getMainWidget();
        projectInstance.gPhotoInstance().findChildrenOfOneWidget(mainWidget);
        std::vector<CameraWidget*>& widgetsVector = projectInstance.gPhotoInstance().getWidgetsVector();
        widgetForListOfParam->setFixedHeight(50*widgetsVector.size());

        for (int i = 0; i<widgetsVector.size(); ++i) {

            QWidget * widgetOfOneParam = new QWidget(this);
            layoutForListOfParam->addWidget(widgetOfOneParam);
            QHBoxLayout * layoutForOneParam = new QHBoxLayout(this);
            widgetOfOneParam->setLayout(layoutForOneParam);

            //Label (What param)
            QLabel * labelParam = new QLabel(this);
            labelParam->setText(QString::fromStdString(projectInstance.gPhotoInstance().getNameOfAWidget(widgetsVector.at(i))));
            layoutForOneParam->addWidget(labelParam);


            int type = projectInstance.gPhotoInstance().getTypeWidget(widgetsVector.at(i));

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

                case GP_WIDGET_TOGGLE:
                {
                /*NPO RECUPERER LA VALEUR PAR DEFAULT*/

//                    GPhotoWidgetToggle * toggle = new GPhotoWidgetToggle( widgetsVector.at(i)/*, this*/);
//                    /*make the menu*/
//                    QButtonGroup toggleChoice = toggle->makeButton();
//                    layoutForOneParam->addWidget(&toggleChoice);
//                    toggle->putChoicesIntoButtonGroup();

                    GPhotoWidgetToggle * yes = new GPhotoWidgetToggle( widgetsVector.at(i)/*, this*/);
                    GPhotoWidgetToggle * no = new GPhotoWidgetToggle( widgetsVector.at(i)/*, this*/);
                    /*make the menu*/
                    QRadioButton * toggleYes = yes->makeButton("yes");
                    QRadioButton * toggleNo = no->makeButton("no");
                    layoutForOneParam->addWidget(toggleYes);
                    layoutForOneParam->addWidget(toggleNo);


                    break;
                }

                case GP_WIDGET_TEXT:
                {
                    GPhotoWidgetTextField * textField = new GPhotoWidgetTextField( widgetsVector.at(i)/*, this*/);

                    QLineEdit * text = textField->makeMenu();
                    layoutForOneParam->addWidget(text);
                    break;
                }
            }

            //If toggle (yes/no)
//            if (type == 4) {

//                //récupérer la valeur par défaut
//                //
//                //

//                QRadioButton * yesChoice = new QRadioButton("yes", this);
//                layoutForOneParam->addWidget(yesChoice);
//                QRadioButton * noChoice = new QRadioButton("no", this);
//                layoutForOneParam->addWidget(noChoice);
//            }

            //If text
//            if (type == 2) {

//                //récupérer la valeur par défaut
//                //
//                //
//                QLineEdit * textField = new QLineEdit(this);
//                layoutForOneParam->addWidget(textField);

//            }
//            //If date
//            if (type == 8) {
//                //don't work with gphoto
//            }
        }

        scrollArea->setWidget(widgetForListOfParam);
    }




    QVBoxLayout * layoutForScrollArea = new QVBoxLayout(this);
    layoutForScrollArea->addWidget(scrollArea);

    //scrollArea->setBackgroundRole(QPalette::Dark);
    //scrollArea->addLayout(layoutForListOfParam);


}
