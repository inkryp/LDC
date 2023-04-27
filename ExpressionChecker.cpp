#include "ExpressionChecker.h"

using namespace ldc;

void ExpressionChecker::setCurrentOperand(char *id) {
  auto &symbol_table = SymbolTable::getInstance();
  if (!symbol_table.checkVariableExists(id)) {
    assert(0 && "Variable does not exist!");
  }
  currentOperand = symbol_table.retrieveFromIdentifier(id);
}

void ExpressionChecker::setCurrentOperand(int integer) {
  SymbolTable::SymbolInfo cur = {INT, integer, false};
  SymbolTable::getInstance().insertTemp(cur);
  currentOperand = cur;
}

void ExpressionChecker::setCurrentOperand(float floatingPoint) {
  SymbolTable::SymbolInfo cur = {FLOAT, floatingPoint, false};
  SymbolTable::getInstance().insertTemp(cur);
  currentOperand = cur;
}
