#include "listwidget.h"

#include <QtCore/QMimeData>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QListWidgetItem>
#include <QtCore/QUrl>

#include <boost/foreach.hpp>
#include <boost/algorithm/string/join.hpp>

#include <sstream>
#include <iostream>

ListWidget::ListWidget(QWidget *parent) :
    QListWidget(parent)
{
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

}


void ListWidget::dragEnterEvent(QDragEnterEvent *event)
{

    event->acceptProposedAction();

}

void ListWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    QList<QUrl> urlList = mimeData->urls();
    for (int i = 0; i < urlList.size(); ++i)
    {
        QString text = urlList.at(i).path();
        QListWidgetItem *item = new QListWidgetItem(QIcon(text), text, this);
        this->addItem(item);
    }

    event->acceptProposedAction();

}

void ListWidget::startDrag(Qt::DropActions supportedActions)
{
    std::cout << "ListWidget::startDrag" << std::endl;

    QByteArray itemData;

    // drag icon
    //QPixmap pixmap = qVariantValue<QPixmap>(item->data(Qt::UserRole));
    //QPoint location = item->data(Qt::UserRole+1).toPoint();

    // data
    //QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    //dataStream << item->text() << location;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("tweedy/mediapath", itemData);

    QList<QUrl> urls;
    BOOST_FOREACH( QModelIndex idx, selectedIndexes() )
    {
        QListWidgetItem * item = this->itemFromIndex( idx );
        urls.push_back(item->text());
    }
    mimeData->setUrls(urls);

    //QMimeData* mimeData = model()->mimeData( selectedIndexes() );
    /*
    std::vector<std::string> filenames;
    BOOST_FOREACH( QModelIndex idx, selectedIndexes() )
    {
        QListWidgetItem * item = this->itemFromIndex( idx );
        filenames.push_back( item->text().toStdString() );
    }
    const std::string enc = boost::algorithm::join( filenames, ":" );
    mimeData->setText( QString::fromStdString(enc) );
    */

    std::cout << "size: " << selectedIndexes().size() << std::endl;
    std::cout << "OOO: " << mimeData->text().toStdString() << std::endl;

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    //drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    //drag->setPixmap(pixmap);

    drag->exec();

}
