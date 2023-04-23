#include "SymbolTable.h"

using namespace ldc;

int SymbolTable::foo(int x) {
  return 42 + x;
}

void SymbolTable::updateCurrentType(const SupportedType& update) {
  currentType = update;
}
