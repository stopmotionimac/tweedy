#include "listwidget.h"

#include "chutier.h"
#include "ui_chutier.h"


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
}

void ListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    //if (event->mimeData()->hasImage())
    event->acceptProposedAction();
}

void ListWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    /*if (mimeData->hasImage()) {
             this->addItem(qvariant_cast<QString>(mimeData->imageData()));
    }*/

    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;
    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty())
        return;

    event->acceptProposedAction();

    /*QList<QListWidgetItem *> list = items( event->mimeData() );

            if (!list.isEmpty())
            {
                    QList<QListWidgetItem *>::iterator iter;
                    for (iter = list.begin(); iter != list.end(); ++iter);
                    {
                            QString text = event->mimeData()->text();
                            QListWidgetItem *item = new QListWidgetItem(QIcon(text), text, this);
                            this->addItem(item);
                    }
            }*/
}
