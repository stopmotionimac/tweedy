#ifndef ADDCOMMAND_HPP
#define	ADDCOMMAND_HPP

#include "Somme.hpp"
#include <tweedy/core/IUndoRedoCommand.hpp>

class AddCommand : public IUndoRedoCommand
 {
 public:
     
     AddCommand(int i, const std::string& s, Somme& somme): value(i), text(s), target(somme){}
     
     ~AddCommand();
     
     AddCommand* clone() const;
     
     void undo();
     void runDo();
     void redo();
     
     void getName() const;
     void setText(const std::string &text);
     const std::string& getText() const;

 private:
     int value;
     std::string text;
     Somme& target ;
 };

#endif	/* ADDCOMMAND_HPP */

