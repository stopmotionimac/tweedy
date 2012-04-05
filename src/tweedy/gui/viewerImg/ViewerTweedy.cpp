#include "ui_ViewerTweedy.h"

#include "ViewerTweedy.hpp"

#include <tweedy/core/Projet.hpp>


struct ViewerTweedyUpdater
{
	ViewerTweedyUpdater( ViewerTweedy & viewerImg )
	: _viewerImg( viewerImg )
	{
	}

	void operator()()
	{
		_viewerImg.getTempsSlider()->setMaximum( Projet::getInstance().getTimeline().getMaxTime() );
	}

	ViewerTweedy& _viewerImg;
};

ViewerTweedy::ViewerTweedy( QWidget *parent )
: QWidget( parent )
, _ui( new Ui::ViewerTweedy )
{
	_ui->setupUi( this );
	_currentTime = 0;
        _onionAction = new QAction( "onion", this );
	_onionAction->setStatusTip( "Option Onion Skin" );
	_previewTimer = new QTimer( this );

	displayChanged( 0 );

	//connecter l'update de la timelineUi au signalChanged de la timeline
	ViewerTweedyUpdater upd( *this );

	Projet::getInstance().getTimeline().getSignalChanged().connect( upd );

	connect( _ui->spinBox, SIGNAL( valueChanged( int ) ), _onionAction, SLOT( trigger() ) );
	connect( _onionAction, SIGNAL( triggered() ), this, SLOT( handle_onionAction_triggered() ) );
	connect( _previewTimer, SIGNAL( timeout() ), this, SLOT( updatePreview() ) );

        getViewerLabel()->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        getViewerLabel()->setScaledContents( false );

        this->getViewerLabel()->setMinimumSize(this->getViewerLabel()->pixmap()->size());


}

QToolButton * ViewerTweedy::getPlayPauseButton()
{
	return _ui->playPauseButton;
}

QToolButton * ViewerTweedy::getNextButton()
{
	return _ui->nextButton;
}

QToolButton * ViewerTweedy::getPreviousButton()
{
	return _ui->previousButton;
}

QToolButton * ViewerTweedy::getCaptureButton()
{
	return _ui->captureButton;
}

QToolButton * ViewerTweedy::getRetour0Button()
{
	return _ui->retour0Button;
}

QLabel * ViewerTweedy::getViewerLabel()
{
	return _ui->viewerLabel;
}

QLabel * ViewerTweedy::getTimeLabel()
{
	return _ui->timeLabel;
}

QSlider * ViewerTweedy::getTempsSlider()
{
	return _ui->tempsSlider;
}

void ViewerTweedy::displayChanged( int time )
{
	//_ui->spinBox->setValue(0);
	_currentTime = time;
	Timeline* timeline = &( Projet::getInstance().getTimeline() );
	std::string idClip = "";
        std::string filename = "img/none.jpg";

	/*if (time == timeline->maxTime()) {
		//afficher le temps reel
		? ms
		  20 img -> 1sec
		  01 img -> 0.05 sec = 50 ms

		_previewTimer->start(50);
		//filename = "img/realTime.jpg";
	}*/

	_previewTimer->stop();
	bool isClip = timeline->findCurrentClip( idClip, time );
	if( isClip )
	{
		filename = timeline->mapClip()[idClip].imgPath().string();

		if( idClip.find( "flux" ) != std::string::npos )
		{
			_previewTimer->start( 50 );
		}
	}

        QPixmap img( QString::fromStdString( filename ) );
        QPixmap p( img.scaled ( getViewerLabel()->size(), Qt::KeepAspectRatioByExpanding ) );
        this->getViewerLabel()->setPixmap( p );
        this->getViewerLabel()->adjustSize();

	handle_onionAction_triggered();

}

void ViewerTweedy::handle_onionAction_triggered()
{
	int nbFrames = _ui->spinBox->value();
	Timeline t = Projet::getInstance().getTimeline();
	std::string idClip = "img/none.jpg";
	std::string filename = "img/none.jpg";

	int beginTime = _currentTime - nbFrames;
	if( beginTime < 0 )
	{
		nbFrames += beginTime;
		beginTime = 0;
	}
	bool found = t.findCurrentClip( idClip, beginTime );

	QImage resultImage = QImage( QPixmap( QString::fromStdString( filename ) ).size(), QImage::Format_ARGB32_Premultiplied );

	if( found )
	{
		filename = t.mapClip()[idClip].imgPath().string();
	}

	found = resultImage.load( QString::fromStdString( filename ) );

	/*
	//modification de la transparence ???
    
	for (int i=0; i<resultImage.colorCount(); ++i)
	{
		QColor c(resultImage.color(i));
		c.setAlphaF(0.5);
		resultImage.setColor(i, c.rgba());

	}
	 */

	for( int i = 1; i <= nbFrames; ++i )
	{
		if( _currentTime - i < 0 )
			break;

		found = t.findCurrentClip( idClip, beginTime + i );
		QImage destinationImage = QImage( QPixmap( QString::fromStdString( filename ) ).size(), QImage::Format_ARGB32_Premultiplied );

		filename = t.mapClip()[idClip].imgPath().string();

		found = destinationImage.load( QString::fromStdString( filename ) );

		QImage sourceImage( resultImage );

		resultImage = calculateImage( sourceImage, destinationImage );
	}


	resultImage.scaled( this->geometry().size(), Qt::KeepAspectRatioByExpanding );
	this->getViewerLabel()->setPixmap( QPixmap::fromImage( resultImage ) );

}

//capture and display real time

void ViewerTweedy::updatePreview()
{
	Projet& projectInstance = Projet::getInstance();
	int isConnected = projectInstance.gPhotoInstance().tryToConnectCamera();
	if( isConnected == 0 )
	{
		QPixmap noCamera( QString::fromStdString( "img/noCameraDetected.jpg" ) );
		//        noCamera.scaled(this->getViewerLabel()->pixmap()->size(),Qt::KeepAspectRatioByExpanding);
		//        noCamera.scaled(this->geometry().size(), Qt::KeepAspectRatioByExpanding) ;
		this->getViewerLabel()->setPixmap( noCamera );
	}
	else
	{
		std::string filename = projectInstance.gPhotoInstance().doPreview( 1 );
		this->getViewerLabel()->setPixmap( QPixmap( QString::fromStdString( filename ) ) );
		//delete captured file
		boost::filesystem::path FileToDeletePath( filename );
		boost::filesystem::remove( filename );
	}
	//std::cout<<"DO PREVIEW"<<std::endl;
}

QImage ViewerTweedy::calculateImage( const QImage& sourceImage, const QImage& destinationImage )
{
	//    QSize(475,343)
	QImage resultImage = QImage( sourceImage.size(), QImage::Format_ARGB32_Premultiplied );

	QPainter::CompositionMode mode = QPainter::CompositionMode_SoftLight;

	QPainter painter( &resultImage );

	painter.setCompositionMode( QPainter::CompositionMode_Source );
	painter.fillRect( resultImage.rect(), Qt::transparent );
	painter.setCompositionMode( QPainter::CompositionMode_SourceOver );
	painter.drawImage( 0, 0, destinationImage );
	painter.setCompositionMode( mode );
	painter.drawImage( 0, 0, sourceImage );
	painter.setCompositionMode( QPainter::CompositionMode_DestinationOver );
	painter.fillRect( resultImage.rect(), Qt::white );
	painter.end();

	return resultImage;
}

ViewerTweedy::~ViewerTweedy()
{
	delete _ui;
}
