#include "tabletimeline.h"

#include <tweedy/core/Projet.hpp>

#include <QtGui/QScrollBar>
#include <QtGui/QListWidget>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDropEvent>
#include <QtCore/QUrl>

#include <boost/algorithm/string.hpp>

#include <iostream>

TableTimeline::TableTimeline(QWidget *parent) :
    QTableWidget(parent)
{
    this->setRowCount(1);
    this->setColumnCount(1);
    
    this->setIconSize(QSize(80, 80));
    
    QTableWidgetItem * itemColonne1 = new QTableWidgetItem("Flux video");
    this->setHorizontalHeaderItem(0,itemColonne1);

    QTableWidgetItem * itemLigne1 = new QTableWidgetItem("Sequence");
    this->setVerticalHeaderItem(1,itemLigne1);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
}

void TableTimeline::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}


void TableTimeline::dragMoveEvent(QDragMoveEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void TableTimeline::dropEvent(QDropEvent *event)
{
    std::cout<<"TableTimeline::dropEvent"<<std::endl;
    //on recupere la timeline
    Timeline * timeline = &(Projet::getInstance().getTimeline());


    //on recupere le mimeData (ce que l'on drag)
    const QMimeData* data = event->mimeData();

    //on recupere la position
    QTableWidgetItem * item = itemAt(event->pos());
    unsigned int position = item->column();
    std::cout << "y: " << item->column() << std::endl;

    QList<QUrl> urlList = data->urls();
    for(int i = 0; i < urlList.size() ; ++i)
    {
        QString text = urlList.at(i).path();
        std::string data = text.toStdString();

        std::cout << "TL: " << data << std::endl;

        //ajout du clip dans la timeline core
        timeline->insertClip(data, position);
    }

    /*std::vector<std::string> filenames;
    boost::algorithm::split( filenames, datas, boost::is_any_of(":") );
    std::cout << "TL: " << filenames.size() << std::endl;*/

    event->acceptProposedAction();


}
