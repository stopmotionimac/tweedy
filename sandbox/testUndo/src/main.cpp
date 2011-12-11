#include "UndoRedoCommand.hpp"
#include "UndoView.hpp"

#include <cstdlib>
#include <iostream>



int main(){
    
    /* simple test on CommandManager */
   
    CommandManager cmdMan ;
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;
    
    cmdMan.pushNewCommand(new AddCommand(2,"command +2", cmdMan.getSomme()));
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;

    cmdMan.undo();
    
    std::cout << cmdMan.getSomme().getSommeValue() << std::endl;
    
    return EXIT_SUCCESS;
}

