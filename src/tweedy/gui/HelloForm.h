/* 
 * File:   HelloForm.h
 * Author: Julien
 *
 * Created on 5 novembre 2011, 23:41
 */

#ifndef _HELLOFORM_H
#define	_HELLOFORM_H

#include "ui_HelloForm.h"

class HelloForm : public QDialog {
    Q_OBJECT
public:
    HelloForm();
    virtual ~HelloForm();
private:
    Ui::HelloForm widget;
};

#endif	/* _HELLOFORM_H */

