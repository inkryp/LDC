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
  currentOperand = {INT, integer};
}

void ExpressionChecker::setCurrentOperand(float floatingPoint) {
  currentOperand = {FLOAT, floatingPoint};
}
