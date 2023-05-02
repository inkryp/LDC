#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "Quadruple.h"
#include <stack>
#include <vector>

namespace ldc {

/// TODO: Come up with a description
class CodeGenerator {
private:
  std::vector<Quadruple> quadruples;
  std::stack<int> pendingJumps;

public:
  /// Implementing a singleton for ExpressionChecker
  static CodeGenerator &getInstance() {
    static CodeGenerator instance;
    return instance;
  }
  void insertQuad(const Quadruple &);
  void dump();
  void pushbackToPendingJumps(int = -1);
  bool fillLastPendingJump(int = 0);
  int popLastPendingJump();
  std::vector<Quadruple> getQuadruples();
};
} // namespace ldc

#endif // CODE_GENERATOR_H
