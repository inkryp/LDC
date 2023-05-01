#ifndef QUADRUPLE_H
#define QUADRUPLE_H

#include "SymbolTable.h"
#include <iostream>
#include <variant>

namespace ldc {

/// TODO: Write a description for this
struct Quadruple {
  enum BinaryOp {
    ADDITION,
    SUBSTRACTION,
    MULTIPLICATION,
    DIVISION,
    LESS_THAN,
    GREATER_THAN,
    OTHER_THAN,
    PLACEHOLDER
  };
  enum Op { ASSIGN, GOTO };
  friend std::ostream &operator<<(std::ostream &os, const Quadruple &quad) {
    if (std::holds_alternative<Quadruple::BinaryOp>(quad.op)) {
      auto op = std::get<Quadruple::BinaryOp>(quad.op);
      switch (op) {
      case Quadruple::BinaryOp::ADDITION:
        os << "ADDITION";
        break;
      case Quadruple::BinaryOp::SUBSTRACTION:
        os << "SUBSTRACTION";
        break;
      case Quadruple::BinaryOp::MULTIPLICATION:
        os << "MULTIPLICATION";
        break;
      case Quadruple::BinaryOp::DIVISION:
        os << "DIVISION";
        break;
      case Quadruple::BinaryOp::LESS_THAN:
        os << "LESS_THAN";
        break;
      case Quadruple::BinaryOp::GREATER_THAN:
        os << "GREATER_THAN";
        break;
      case Quadruple::BinaryOp::OTHER_THAN:
        os << "OTHER_THAN";
        break;
      default:
        os << "SHOULDN'T HAPPEN";
        break;
      }
    } else {
      auto op = std::get<Quadruple::Op>(quad.op);
      switch (op) {
      case Quadruple::Op::ASSIGN:
        os << "ASSIGN";
        break;
      case Quadruple::Op::GOTO:
        os << "OS";
        break;
      default:
        os << "SHOULDN'T HAPPEN";
        break;
      }
    }
    if (quad.left) {
      os << ' ' << quad.left.value()->first;
    }
    if (quad.right) {
      os << ' ' << quad.right.value()->first;
    }
    if (quad.result) {
      os << ' ' << quad.result.value()->first;
    }
    return os;
  }
  std::variant<BinaryOp, Op> op;
  std::optional<SymbolTable::SymbolLocation> left, right, result;
};

} // namespace ldc

#endif // QUADRUPLE_H
