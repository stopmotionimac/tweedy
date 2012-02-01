#include "ConfigCamera.hpp"

ConfigCamera::ConfigCamera(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * layoutForListOfParam = new QVBoxLayout(this);
    /*Add as many layout as we have param on the camera*/
    Projet& projectInstance = Projet::getInstance();

    QScrollArea * scrollArea = new QScrollArea(this);
    //scrollArea->setLayout(layoutForListOfParam);

    int isConnected = projectInstance.tryToConnectCamera();
    std::cout<<"IS CONNECTED ?"<<isConnected<<std::endl;
    if (isConnected == 0)
    {
        //Label for no camera connected
        QLabel * noCameraLabel = new QLabel(this);
        noCameraLabel->setMargin(30);
        noCameraLabel->setText("There is no camera detected");
        layoutForListOfParam->addWidget(noCameraLabel);
    }
    else
    {
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


