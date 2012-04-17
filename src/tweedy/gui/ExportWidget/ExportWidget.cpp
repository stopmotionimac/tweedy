#include "ui_ExportWidget.h"

#include <tweedy/gui/ExportWidget/ExportWidget.hpp>
#include <tweedy/core/Clip.hpp>
#include <tweedy/core/Timeline.hpp>
#include <tweedy/core/Projet.hpp>


#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <fstream>

ExportWidget::ExportWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::ExportWidget)
{
    _ui->setupUi(this);
    
    /* set globalFpsComboBox values */
    _ui->globalFpsComboBox->addItem( QString("24"));
    _ui->globalFpsComboBox->addItem( QString("25"));
    _ui->globalFpsComboBox->addItem( QString("30"));
    
    /* set tweedyFrameComboBox values */
    
    _ui->tweedyFrameComboBox->addItem( QString("1"));
    _ui->tweedyFrameComboBox->addItem( QString("2"));
    _ui->tweedyFrameComboBox->addItem( QString("3"));
    
    /* connect SearchFolderButton with the action */
    connect( _ui->browseButton, SIGNAL( clicked() ), this, SLOT( on_searchFolderProjectButton_clicked() ) );
    
    /* connect the export button*/
    connect( _ui->exportButton, SIGNAL( clicked() ), this, SLOT( on_exportButton_clicked()) );
    
    /* connect the cancel button*/
    connect( _ui->cancelButton, SIGNAL( clicked() ), this, SLOT( on_cancelButton_clicked()) );
    
}

ExportWidget::~ExportWidget()
{
    delete _ui;
}

void ExportWidget::on_searchFolderProjectButton_clicked()
{
    std::cout << " filedialog" << std::endl;
    QFileDialog * fileDialog = new QFileDialog();
    QString fileName = fileDialog->getExistingDirectory( this, tr( "Choose folder for project" ), QString( boost::filesystem::initial_path().string().c_str() ) );

    _ui->exportFolderLineEdit->setText( fileName );
    
    
}

void ExportWidget::on_exportButton_clicked()
{
    if(_ui->exportFolderLineEdit->text().isEmpty() || _ui->exportNameLineEdit->text().isEmpty())
        QMessageBox::about(this, tr("Empty Path"), tr("Please, choose a folder and a name"));
    else
    {
        QString filename = QString(_ui->exportFolderLineEdit->text());
        filename.push_back("/");
        filename.push_back(_ui->exportNameLineEdit->text());
        filename.push_back(".edl");

        std::string globalFpsString = _ui->globalFpsComboBox->currentText().toStdString();
        int globalFps = boost::lexical_cast<int>(globalFpsString);

        std::string tweedyFrameString = _ui->tweedyFrameComboBox->currentText().toStdString();
        int convFrame = boost::lexical_cast<int>(tweedyFrameString);

        std::cout << globalFps << std::endl;
        std::cout << convFrame << std::endl;
        
        generateEDLExport(filename.toStdString(), globalFps, convFrame);

        this->close();

        QMessageBox::about( this, tr( "Export done" ), tr( "Export successful" ) );
    }
        
    
    
}


void ExportWidget::on_cancelButton_clicked()
{
    this->close();
}


void ExportWidget::generateEDLExport(std::string filename, int globalFps, int convFrame )
{
    std::cout << "export EDL" << std::endl;
        
        const std::string fileNameEDLExport = filename;
        std::ofstream myFlux(fileNameEDLExport.c_str());
        
        if(myFlux)
        {
            int i = 1;
            
            /* A MODIFIER */
            double fps = globalFps/convFrame;
            
            std::cout << fps << std::endl;
            
            typedef boost::ptr_map<unsigned int, Clip*> OMapClip;
            Timeline timeline = Projet::getInstance().getTimeline();
            OMapClip mapClip = timeline.getOrderedClips();
         
            /* code pour générer le fichier edl*/
            myFlux << "TITLE: Tweedy" << std::endl;
            myFlux << std::endl;
            
            /*  work directory */
            //myFlux << "*WORK DIR = TWEEDY/IMG"<<std::endl;
            //myFlux << std::endl;
            
            BOOST_FOREACH( const OMapClip::value_type& s, mapClip )
            {
                Clip* clip = *s->second;
                
                if( clip->timeOut() != timeline.getMaxTime() )
                {
                    int length = clip->timeOut() - clip->timeIn();

                    


                    std::vector<std::string> strs;
                    const std::string st = clip->getImgPath().string();
                    boost::split(strs, st,boost::is_any_of("/"));
                    std::string nameImg = strs.back();

                    myFlux << boost::lexical_cast<std::string>(i) + "  AX       V     C        " ;
                    myFlux << generateTimeData(0,fps,globalFps) ;
                    myFlux << " " + generateTimeData(length,fps,globalFps) ;
                    myFlux << " " + generateTimeData(clip->timeIn(),fps,globalFps) ;
                    myFlux << " " + generateTimeData(clip->timeOut(),fps,globalFps) << std::endl ;

                    /* etablir le nom de l'image */
                    myFlux << "* FROM CLIP NAME: " + nameImg << std::endl<<std::endl;
                }
                ++i;
                
            }
            
            
        }
        else
        {
            std::cout << "Impossible d'ouvrir le fichier d'export EDL" << std::endl;
        }
}


std::string ExportWidget::generateTimeData(int value, int choosenFps, int absoluteFps)
{
    double cAbsoluteFps = static_cast<double>(absoluteFps);
    
    //convertir la lgr du clip en base 24
    int nbframe = value * (absoluteFps/choosenFps);
    int hour = nbframe/std::pow(cAbsoluteFps,3);
    int min = (nbframe % static_cast<int>(std::pow(cAbsoluteFps,3)))/std::pow(cAbsoluteFps,2);
    int sec = (nbframe % static_cast<int>(std::pow(cAbsoluteFps,2)))/absoluteFps;
    nbframe = nbframe % absoluteFps ;
    
    std::string shour = hour<10 ? "0"+boost::lexical_cast<std::string>(hour) 
            : boost::lexical_cast<std::string>(hour);

    std::string smin = min<10 ? "0"+boost::lexical_cast<std::string>(min) 
            : boost::lexical_cast<std::string>(min);

    std::string ssec = sec<10 ? "0"+boost::lexical_cast<std::string>(sec) 
            : boost::lexical_cast<std::string>(sec);

    std::string sframe = nbframe<10 ? "0"+boost::lexical_cast<std::string>(nbframe) 
            : boost::lexical_cast<std::string>(nbframe);

    return shour + ":" + smin + ":" + ssec + ":" + sframe ;
}
