#ifndef ADDCOMMAND_HPP
#define	ADDCOMMAND_HPP

#include "Somme.hpp"
#include <tweedy/core/IUndoRedoCommand.hpp>

class AddCommand : public IUndoRedoCommand
 {
    
 public:
     AddCommand(int i, std::string s, Somme& somme): value(i), text(s), target(somme){
         
     }
     
     ~AddCommand(){};
     
     
     virtual void undo();
     virtual void runDo();
     virtual void redo();
     
     virtual void getName() const;
     virtual void setText(const std::string &text);
     virtual std::string getText();

 private:
     int value;
     std::string text;
     Somme& target ;
 };

#endif	/* ADDCOMMAND_HPP */

