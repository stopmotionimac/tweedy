#include "listwidget.h"

#include <QtCore/QMimeData>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QListWidgetItem>
#include <QtCore/QUrl>


ListWidget::ListWidget(QWidget *parent) :
    QListWidget(parent)
{
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setSelectionMode(QAbstractItemView::ContiguousSelection);

    this->setMaximumSize(parent->width()/2, parent->height());
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
