/* 
 * File:   ImageComposer.cpp
 * Author: julien
 * 
 * Created on 26 janvier 2012, 14:19
 */

#include "ImageComposer.h"

ImageComposer::ImageComposer() 
{
    _spinBox = new QSpinBox();
    _spinBox->setMinimum(1);
    _spinBox->setMaximum(5);
    _spinBox->setValue(1);
    
    _operatorComboBox = new QComboBox;
    _operatorComboBox->addItem(tr("Onion Skin"), QPainter::CompositionMode_SoftLight);
    
    QHBoxLayout * layoutButtons = new QHBoxLayout(this);
    layoutButtons->addWidget(_spinBox);
    
    _resultLabel = new QLabel;
    
    _resultImage = QImage(QSize(475,343), QImage::Format_ARGB32_Premultiplied);
    
    //connect(_operatorComboBox, SIGNAL(activated(int)),this, SLOT(recalculateResult()));
}






void ImageComposer::recalculateResult(const QImage& sourceImage, const QImage& destinationImage)
 {
     QPainter::CompositionMode mode = QPainter::CompositionMode_SoftLight;

     QPainter painter(&_resultImage);
     painter.setCompositionMode(QPainter::CompositionMode_Source);
     painter.fillRect(_resultImage.rect(), Qt::transparent);
     painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
     painter.drawImage(0, 0, destinationImage);
     painter.setCompositionMode(mode);
     painter.drawImage(0, 0, sourceImage);
     painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
     painter.fillRect(_resultImage.rect(), Qt::white);
     painter.end();

     _resultLabel->setPixmap(QPixmap::fromImage(_resultImage));
 }