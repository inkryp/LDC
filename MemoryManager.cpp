#include "MemoryManager.h"
#include "SymbolTable.h"
#include <iostream>
using namespace ldc;

void MemoryManager::initializeMemory() {
  const auto &amtEachType = SymbolTable::getInstance().getAmountEachType();
  for (const auto &val : amtEachType) {
    mem.emplace_back(
        std::vector<std::variant<int, float, bool, std::string>>(val));
  }
  assert(mem.size() == 4);
  const auto &table = SymbolTable::getInstance().getTable();
  for (const auto &[key, val] : table) {
    auto pos = std::get<3>(val);
    auto &mem = getMemoryLocation(pos);
    mem = std::get<1>(val);
  }
}

std::variant<int, float, bool, std::string> &
MemoryManager::getMemoryLocation(std::pair<int, int> loc) {
  return mem[loc.first][loc.second];
}
