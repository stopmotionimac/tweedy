#ifndef UNDOVIEW_HPP
#define	UNDOVIEW_HPP

#include "UndoRedoCommand.hpp"

#include <boost/ptr_container/ptr_vector.hpp>
#include <QtGui/QListView>
#include <QtGui/QUndoGroup>

class UndoView : public QListView{
    
public:
        
        UndoView(CommandManager * cmdManager, QWidget * parent = 0) 
                : QListView(parent), cmdMan(cmdManager){
                    
        }
        
        ~UndoView();

        QIcon cleanIcon() const;
        void setCleanIcon(const QIcon & icon);
        
        QString	getEmptyLabel () const;
        void setEmptyLabel( const QString & label );
        
        QUndoGroup * group() const;
        
        boost::ptr_vector<IUndoRedoCommand>* stack() const;


private Q_SLOTS:
    void setGroup ( QUndoGroup * group);
    void setStack ( boost::ptr_vector<IUndoRedoCommand>* undoStack);
    
private:
       
    QIcon icon;
    QString emptyLabel;
    CommandManager* cmdMan;
    QUndoGroup * undoGroup;
        
};
#endif	/* UNDOVIEW_HPP */

