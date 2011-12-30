#include "tweedy/gui/Undo/UndoWidget.hpp"
#include <QT/QtGui>
#include <cstdlib>
#include <iostream>



int main(int argc, char *argv[]){
    
    /* simple test on CommandManager */
   
    CommandManager cmdMan ;
    
    IUndoRedoCommand* addCmd1 = new AddCommand(2,"AddCommand1(+2)",cmdMan.getSomme());
    IUndoRedoCommand* dltCmd1 = new DeleteCommand(4,"DeleteCommand1(-4)",cmdMan.getSomme());
    IUndoRedoCommand* addCmd2 = new AddCommand(20,"AddCommand2(+20)",cmdMan.getSomme());
    IUndoRedoCommand* dltCmd2 = new DeleteCommand(1,"DeleteCommand2(-1)",cmdMan.getSomme());
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;
    
    cmdMan.pushNewCommand(addCmd1);
    cmdMan.pushNewCommand(dltCmd1);
    cmdMan.pushNewCommand(addCmd2);
    
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;

    cmdMan.undo();
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;
    
    cmdMan.pushNewCommand(dltCmd2);
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;
    
    std::cout << "It's gonna undooooing" << std::endl;
    
    for(int i = 0; i <3;++i)    cmdMan.undo();
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;
    
    std::cout << "It's gonna redooooing" << std::endl;
    
    for(int i = 0; i <3;++i)    cmdMan.redo();
    
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;
   
    
    
    
    QApplication app(argc, argv);
    

    
    UndoView* undoView = new UndoView(&cmdMan);
    
    QWidget * undoWidget = new UndoWidget(undoView);
    undoWidget->setWindowTitle("Command List");
    undoWidget->show();
    
    
    
    return app.exec();
    
    //return EXIT_SUCCESS;
}

