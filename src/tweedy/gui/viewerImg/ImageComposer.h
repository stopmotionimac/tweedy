/* 
 * File:   ImageComposer.h
 * Author: julien
 *
 * Created on 26 janvier 2012, 14:19
 */

#ifndef IMAGECOMPOSER_H
#define	IMAGECOMPOSER_H

#include <QtGui/QComboBox>
#include <QtGui/QLabel>
#include <QtGui/QPainter>
#include <QtGui/QSpinBox>
#include <QtGui/QHBoxLayout>


class ImageComposer:public QWidget
{
    
    Q_OBJECT
    
public:
    ImageComposer();
    
    
private Q_SLOTS:
    void recalculateResult(const QImage& sourceImage, const QImage& destinationImage);
    
private:
    QSpinBox * _spinBox;
    QComboBox * _operatorComboBox;
    QLabel * _resultLabel;
    QImage _resultImage;
};

#endif	/* IMAGECOMPOSER_H */

