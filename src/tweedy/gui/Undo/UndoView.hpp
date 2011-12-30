#ifndef UNDOVIEW_HPP
#define	UNDOVIEW_HPP

#include <tweedy/core/IUndoRedoCommand.hpp>
#include <tweedy/core/CommandManager.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <QtGui/QListView>
#include <QtGui/QUndoGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>


class UndoView : public QListWidget{
    Q_OBJECT
public:
        UndoView(QWidget* parent =0);
        UndoView(CommandManager * cmdManager, QWidget * parent = 0) 
                : QListWidget(parent), p_cmdMan(cmdManager){
        }
        
        UndoView(QUndoGroup * group, QWidget * parent = 0): undoGroup(group){}
        
        ~UndoView();

        QIcon cleanIcon() const;
        void setCleanIcon(const QIcon & icon);
        
        QString	getEmptyLabel () const;
        void setEmptyLabel( const QString & label );
        
        QUndoGroup * group() const;
       
        ///###useless
        //std::stack<IUndoRedoCommand*>& stack() const;
        
        
        //void fillStringUndoStack();
        //void fillStringRedoStack();
        ///###
        
        void fill();

        CommandManager* getCmdMan();

private Q_SLOTS:
    //void setGroup ( QUndoGroup * group);
    //void setStack ( boost::ptr_vector<IUndoRedoCommand>* undoStack);
    
private:
       
    QIcon icon;
    QString emptyLabel;
    CommandManager* p_cmdMan;
    QUndoGroup * undoGroup;
    std::stack<QString> pileString;
        
};
#endif	/* UNDOVIEW_HPP */

