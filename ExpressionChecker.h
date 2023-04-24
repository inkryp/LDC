#ifndef EXPRESSION_CHECKER_H
#define EXPRESSION_CHECKER_H

#include "SymbolTable.h"
#include <stack>

namespace ldc {

struct Quadruple {
  enum Op { MULTIPLICATION, DIVISION, ADDITION, SUBSTRACTION };
  Op op;
  SymbolTable::SymbolInfo left, right, result;
};

/// TODO: Come up with a description
class ExpressionChecker {
private:
  std::stack<SymbolTable::SymbolInfo> operands;
  std::stack<Quadruple::Op> operators;
  SymbolTable::SymbolInfo currentOperand;

public:
  /// Implementing a singleton for ExpressionChecker
  static ExpressionChecker &getInstance() {
    static ExpressionChecker instance;
    return instance;
  }
  void setCurrentOperand(char *);
  void setCurrentOperand(int);
  void setCurrentOperand(float);
  void check();
};
} // namespace ldc

#endif // EXPRESSION_CHECKER_H