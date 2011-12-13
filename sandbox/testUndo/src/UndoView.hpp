#ifndef UNDOVIEW_HPP
#define	UNDOVIEW_HPP

#include "UndoRedoCommand.hpp"

#include <boost/ptr_container/ptr_vector.hpp>
#include <QtGui/QListView>
#include <QtGui/QUndoGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>


class UndoView : public QListWidget{
    Q_OBJECT
public:
        UndoView(QWidget* parent =0);
        UndoView(CommandManager * cmdManager, QWidget * parent = 0) 
                : QListWidget(parent), cmdMan(cmdManager){
                    
        }
        UndoView(QUndoGroup * group, QWidget * parent = 0): undoGroup(group){}
        
        ~UndoView();

        QIcon cleanIcon() const;
        void setCleanIcon(const QIcon & icon);
        
        QString	getEmptyLabel () const;
        void setEmptyLabel( const QString & label );
        
        QUndoGroup * group() const;
        
        std::stack<IUndoRedoCommand*>& stack() const;
        
        void fillStringStack();
        void fill();


private Q_SLOTS:
    //void setGroup ( QUndoGroup * group);
    //void setStack ( boost::ptr_vector<IUndoRedoCommand>* undoStack);
    
private:
       
    QIcon icon;
    QString emptyLabel;
    CommandManager* cmdMan;
    QUndoGroup * undoGroup;
    std::stack<QString> pileString;
        
};

class UndoWidget: public QWidget{
public:
    
    UndoWidget(UndoView * undoView);
    ~UndoWidget();
    
private:
    QVBoxLayout * dockLayout;
    QPushButton * addButton;
    QPushButton * dltButton;
    UndoView* undoView;
};
 
#endif	/* UNDOVIEW_HPP */

