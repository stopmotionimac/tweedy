#include "ConfigCamera.hpp"

ConfigCamera::ConfigCamera(QWidget *parent) : QWidget(parent)
{
    Projet& projectInstance = Projet::getInstance();

    QScrollArea * scrollArea = new QScrollArea(this);

    /*Add as many layout as we have param on the camera*/

    int isConnected = projectInstance.tryToConnectCamera();
    //std::cout<<"IS CONNECTED ?"<<isConnected<<std::endl;
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
        //Chance size in fonction of nuber of config

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

            //If radio
            //if (projectInstance.gPhotoInstance().isRadioOrMenu(widgetsVector.at(i))) {
            if (type == 5) {

                //récupérer la valeur par défaut
                //
                //

                int nbChoices = projectInstance.gPhotoInstance().CountChoices(widgetsVector.at(i));
                //std::cout<<"NB CHOICES : "<<nbChoices<<std::endl;

                //For the QMenu
                QMenu * menuChoice = new QMenu(this);
                QPushButton * buttonChoice = new QPushButton(this);
                buttonChoice->setMenu(menuChoice);

                layoutForOneParam->addWidget(buttonChoice);


                //get each choices to make a menu
                for (int j = 0; j< nbChoices; ++j) {
                    std::string choiceName = projectInstance.gPhotoInstance().getChoice(widgetsVector.at(i), j);
                    //std::cout<<"NAME CHOICE => "<<choiceName<<std::endl;
                    menuChoice->addMenu(QString::fromStdString(choiceName));
                }
            }
            //If toggle (yes/no)
            if (type == 4) {

                //récupérer la valeur par défaut
                //
                //

                QRadioButton * yesChoice = new QRadioButton("yes", this);
                layoutForOneParam->addWidget(yesChoice);
                QRadioButton * noChoice = new QRadioButton("no", this);
                layoutForOneParam->addWidget(noChoice);
            }
            //If text
            if (type == 2) {

                //récupérer la valeur par défaut
                //
                //
                QLineEdit * textField = new QLineEdit(this);
                layoutForOneParam->addWidget(textField);

            }
            //If date
            if (type == 8) {
                //pb ac gphoto

                //récupérer la valeur par défaut
                //
                //
            }
        }



        scrollArea->setWidget(widgetForListOfParam);

//        QLabel * label1 = new QLabel(this);
//        layoutForListOfParam->addWidget(label1);
//        label1->setText("LABEL 1");
//        QLabel * label2 = new QLabel(this);
//        label2->setText("LABEL 2");
//        layoutForListOfParam->addWidget(label2);
//        QLabel * label3 = new QLabel(this);
//        layoutForListOfParam->addWidget(label3);
//        label3->setText("LABEL 3");
//        QLabel * label4 = new QLabel(this);
//        label4->setText("LABEL 4");
//        layoutForListOfParam->addWidget(label4);
//=> se resize
    }




    QVBoxLayout * layoutForScrollArea = new QVBoxLayout(this);
    layoutForScrollArea->addWidget(scrollArea);

    //scrollArea->setBackgroundRole(QPalette::Dark);
    //scrollArea->addLayout(layoutForListOfParam);


}


