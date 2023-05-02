#include "CodeGenerator.h"
#include "Quadruple.h"
#include <iostream>

using namespace ldc;

void CodeGenerator::insertQuad(const Quadruple &quad) {
  quadruples.push_back(quad);
}

void CodeGenerator::dump() {
  for (auto &quad : quadruples) {
    std::cout << quad << '\n';
  }
}

void CodeGenerator::pushbackToPendingJumps(int pos /*= -1*/) {
  pendingJumps.push(quadruples.size() + pos);
}

bool CodeGenerator::fillLastPendingJump(int cnt /*= 0*/) {
  if (pendingJumps.empty()) {
    std::cerr << "Error: Something went wrong in the compiler side of things\n"
              << "This event should never actually happen\n";
    return false;
  }
  auto currentEnd = pendingJumps.top();
  pendingJumps.pop();
  quadruples[currentEnd].result = static_cast<int>(quadruples.size()) - cnt;
  return true;
}

int CodeGenerator::popLastPendingJump() {
  if (pendingJumps.empty()) {
    std::cerr << "Error: Something went wrong in the compiler side of things\n"
              << "This event should never actually happen\n";
    return false;
  }
  auto val = pendingJumps.top();
  pendingJumps.pop();
  return val;
}
