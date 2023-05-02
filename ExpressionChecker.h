#ifndef EXPRESSION_CHECKER_H
#define EXPRESSION_CHECKER_H

#include "Quadruple.h"
#include "SymbolTable.h"
#include <optional>
#include <stack>
#include <vector>

namespace ldc {

/// TODO: Come up with a description
class ExpressionChecker {
private:
  typedef std::variant<int, float, bool> VariantType;
  std::stack<SymbolTable::SymbolLocation> operands;
  std::stack<Quadruple::BinaryOp> operators;
  SymbolTable::SymbolLocation currentOperand, currentReturnValue;
  static const std::vector<std::vector<std::vector<SupportedType>>>
      semanticCube;

public:
  /// Implementing a singleton for ExpressionChecker
  static ExpressionChecker &getInstance() {
    static ExpressionChecker instance;
    return instance;
  }
  void setCurrentReturnValue(char *);
  void setCurrentOperand(char *);
  void setCurrentOperand(int);
  void setCurrentOperand(float);
  void insertCurrentOperand();
  void insertOperator(const Quadruple::BinaryOp &);
  bool removeOperatorPlaceholder();
  std::optional<Quadruple::BinaryOp> peekOperator();
  bool executeOperation();
  bool check();
  bool checkBoolExpression();
  bool insertGotoFalse();
};
} // namespace ldc

#endif // EXPRESSION_CHECKER_H