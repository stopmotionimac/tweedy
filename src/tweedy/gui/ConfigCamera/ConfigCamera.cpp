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
                projectInstance.gPhotoInstance().getValue(widgetsVector.at(i));

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
                    //menuChoice->addMenu(QString::fromStdString(choiceName));

                    /*make the appropriate action*/
                    _setValue = new QAction(this);
                    _setValue = menuChoice->addAction(QString::fromStdString(choiceName));

                    menuChoice->addAction(_setValue);
                    connect(_setValue, SIGNAL(triggered()), this, SLOT(on_setValue_triggered(/*widgetsVector.at(i), choiceName*/)));

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
                //don't work with gphoto
            }
        }

        scrollArea->setWidget(widgetForListOfParam);
    }




    QVBoxLayout * layoutForScrollArea = new QVBoxLayout(this);
    layoutForScrollArea->addWidget(scrollArea);

    //scrollArea->setBackgroundRole(QPalette::Dark);
    //scrollArea->addLayout(layoutForListOfParam);


}

void ConfigCamera::on_setValue_triggered(/*CameraWidget *widget, const void *value*/) {
    Projet& projectInstance = Projet::getInstance();
   // projectInstance.gPhotoInstance().setValue(widget, value);
    std::cout<<"OK ACTION"<<std::endl;

}
