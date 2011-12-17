/* 
 * File:   ViewerImg.h
 * Author: julien
 *
 * Created on 13 décembre 2011, 23:05
 */

#ifndef _VIEWERIMG_H
#define	_VIEWERIMG_H


#include <QtGui/QDockWidget>
#include "ui_ViewerImg.h"

namespace Ui{
    class ViewerImg;
}

class ViewerImg : public QDockWidget {
    Q_OBJECT
public:
    ViewerImg();
    ~ViewerImg();
    
    Ui::ViewerImg* getUi()
    {
        return ui;
    }
private:
    Ui::ViewerImg* ui;
};

#endif	/* _VIEWERIMG_H */

