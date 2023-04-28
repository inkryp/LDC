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
