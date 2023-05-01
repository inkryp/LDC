#include "ExpressionChecker.h"
#include "CodeGenerator.h"
#include "Quadruple.h"
#include "SemanticCube.h"
#include <iostream>
#include <optional>
#include <variant>

using namespace ldc;

void ExpressionChecker::setCurrentReturnValue(char *id) {
  auto &symbol_table = SymbolTable::getInstance();
  if (!symbol_table.checkVariableExists(id)) {
    assert(0 && "Variable does not exist!");
  }
  currentReturnValue = symbol_table.retrieveFromIdentifier(id);
}

void ExpressionChecker::setCurrentOperand(char *id) {
  auto &symbol_table = SymbolTable::getInstance();
  if (!symbol_table.checkVariableExists(id)) {
    assert(0 && "Variable does not exist!");
  }
  currentOperand = symbol_table.retrieveFromIdentifier(id);
}

void ExpressionChecker::setCurrentOperand(int integer) {
  SymbolTable::SymbolInfo cur = {INT, integer, false};
  auto result = SymbolTable::getInstance().insertTemp(cur);
  if (!result.second) {
    assert(0 && "There was an error when inserting a temporary value");
  }
  currentOperand = result.first;
}

void ExpressionChecker::setCurrentOperand(float floatingPoint) {
  SymbolTable::SymbolInfo cur = {FLOAT, floatingPoint, false};
  auto result = SymbolTable::getInstance().insertTemp(cur);
  if (!result.second) {
    assert(0 && "There was an error when inserting a temporary value");
  }
  currentOperand = result.first;
}

void ExpressionChecker::insertCurrentOperand() {
  operands.push(currentOperand);
}

bool ExpressionChecker::removeOperatorPlaceholder() {
  if (operators.top() != Quadruple::BinaryOp::PLACEHOLDER) {
    std::cerr << "Error";
    return false;
  }
  operators.pop();
  return true;
}

std::optional<Quadruple::BinaryOp> ExpressionChecker::peekOperator() {
  if (!operators.empty()) {
    return operators.top();
  }
  return {};
}

bool ExpressionChecker::executeOperation() {
  assert(!operators.empty() && "Should never happen");
  auto operation = operators.top();
  operators.pop();
  auto right = operands.top();
  operands.pop();
  auto left = operands.top();
  operands.pop();
  auto returnType = semanticCube[std::get<0>(left->second)]
                                [std::get<0>(right->second)][operation];
  SymbolTable::SymbolInfo generatedSymbol;
  switch (returnType) {
  case SupportedType::INT:
    generatedSymbol = {INT, int(), false};
    break;
  case SupportedType::FLOAT:
    generatedSymbol = {FLOAT, float(), false};
    break;
  case SupportedType::BOOL:
    generatedSymbol = {BOOL, bool(), false};
    break;
  case SupportedType::UNDEFINED:
    std::cerr << "Type mismatch\nCannot do operations with "
              << std::get<0>(left->second) << " and "
              << std::get<0>(right->second) << " using " << operation << '\n';
    return false;
  }
  auto result = SymbolTable::getInstance().insertTemp(generatedSymbol);
  if (!result.second) {
    assert(0 && "There was an error when inserting a temporary value");
  }
  currentOperand = result.first;
  CodeGenerator::getInstance().insertQuad(
      {operation, left, right, currentOperand});
  insertCurrentOperand();
  return true;
}

void ExpressionChecker::insertOperator(const Quadruple::BinaryOp &operation) {
  operators.push(operation);
}

bool ExpressionChecker::check() {
  if (std::get<0>(currentReturnValue->second) != std::get<0>(currentOperand->second)) {
    std::cerr << "Error: Type mismatch\nCannot assign value of expression to variable\n";
    return false;
  }
  CodeGenerator::getInstance().insertQuad(
      {Quadruple::Op::ASSIGN, currentOperand, {}, currentReturnValue});
  return true;
}
