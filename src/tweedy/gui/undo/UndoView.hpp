#ifndef UNDOVIEW_HPP
#define	UNDOVIEW_HPP

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
        UndoView(CommandManager& cmdManager, QWidget * parent = 0);

        
        //UndoView(QUndoGroup * group, QWidget * parent = 0):undoGroup(group){}
        
        ~UndoView();

        QIcon cleanIcon() const;
        void setCleanIcon(const QIcon & icon);
        
        QString	getEmptyLabel () const;
        void setEmptyLabel( const QString & label );
        
        QUndoGroup * group() const;
        
        void fill();

        CommandManager& getCmdMan();

private Q_SLOTS:
    //void setGroup ( QUndoGroup * group);
    //void setStack ( boost::ptr_vector<IUndoRedoCommand>* undoStack);
    
private:
       
    QIcon _icon;
    QString _emptyLabel;
    CommandManager& _cmdMan;
    QUndoGroup * _undoGroup;
    std::stack<QString> _pileString;
    
        
};
#endif	/* UNDOVIEW_HPP */

