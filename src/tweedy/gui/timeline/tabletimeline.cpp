#include "tabletimeline.h"

#include <QtGui/QScrollBar>
#include <QtGui/QListWidget>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDropEvent>

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

    this->setHorizontalScrollMode(ScrollPerPixel);

    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
}

void TableTimeline::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::CopyAction);
    event->accept();
}

void TableTimeline::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
    event->setDropAction(Qt::MoveAction);
}

void TableTimeline::dropEvent(QDropEvent *event)
{
    //this->insertColumn();
    //addItem(event->mimeData()->text());
    //event->setDropAction(Qt::MoveAction);
    /*QList<QTableWidgetItem *> itemListe = selectedItems();
    int colonne = itemAt(event->pos())->column();
    int ligne = itemAt(event->pos())->row();
    foreach(QTableWidgetItem *piece,itemListe )
    {
        int colonneItem = piece->column();
        int ligneItem = piece->row();
        int colonneArrive = colonne + colonneItem;
        int ligneArrive = ligne + ligneItem;
        item(ligneArrive,colonneArrive)->setText(item(ligneItem,colonneItem)->text());
        item(ligneItem,colonneItem)->setText("");
     }
     if (children().contains(event->source()))
     {
        event->setDropAction(Qt::MoveAction);
        event->accept();
     }
     else
     {
        event->acceptProposedAction();
     }*/
}
