#ifndef DELETECOMMAND_HPP
#define	DELETECOMMAND_HPP

#include "Somme.hpp"
#include "IUndoRedoCommand.hpp"

 class DeleteCommand : public IUndoRedoCommand
 {
    
 public:
     DeleteCommand(int i, std::string s, Somme& somme): value(i), text(s), target(somme){
         
     }
     
     ~DeleteCommand(){}
     
     
     virtual void undo();
     virtual void runDo();
     virtual void redo();
     
     virtual void getName() const;
     virtual void setText(const std::string &text);
     
     virtual std::string getText();

     /*
     bool operator==(const DeleteCommand& o)const;
    
     bool operator==(const ICommand& o)const;
     */
 private:
     int value;
     std::string text;
     Somme& target;
 };



#endif	/* DELETECOMMAND_HPP */

