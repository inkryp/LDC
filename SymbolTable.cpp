#include "SymbolTable.h"
#include <iostream>
#include <utility>

using namespace ldc;

void SymbolTable::updateCurrentType(const SupportedType &update) {
  currentType = update;
}

SupportedType SymbolTable::getCurrent() { return currentType; }

void SymbolTable::insert(const char *id) {
  std::variant<int, float> valToBeAssigned;
  switch (currentType) {
  case INT:
    valToBeAssigned = int();
    break;
  case FLOAT:
    valToBeAssigned = float();
    break;
  default:
    assert(0 && "This should never occur");
  }
  auto res = table.find(id);
  if (res != table.end()) {
    assert(0 && "Variable already declared");
  }
  table.insert(
      std::make_pair(id, std::make_tuple(currentType, valToBeAssigned)));
}

void SymbolTable::checkVariableExists(const char *id) {
  auto res = table.find(id);
  if (res == table.end()) {
    assert(0 && "Variable does not exist!");
  }
}

void SymbolTable::printTable() {
  std::cout << "Printing all values:\n";
  for (auto &[key, val] : table) {
    auto hereType = std::get<0>(val);
    std::cout << key << ' ' << std::get<0>(val) << ' ';
    if (hereType == INT) {
      std::cout << std::get<int>(std::get<1>(val)) << '\n';
    } else {
      std::cout << std::get<float>(std::get<1>(val)) << '\n';
    }
  }
}
