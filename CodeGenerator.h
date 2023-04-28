#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "Quadruple.h"
#include <vector>

namespace ldc {

/// TODO: Come up with a description
class CodeGenerator {
private:
  std::vector<Quadruple> quadruples;

public:
  /// Implementing a singleton for ExpressionChecker
  static CodeGenerator &getInstance() {
    static CodeGenerator instance;
    return instance;
  }
  void insertQuad(const Quadruple &);
  void dump();
};
} // namespace ldc

#endif // CODE_GENERATOR_H
