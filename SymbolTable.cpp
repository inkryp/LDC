#include "SymbolTable.h"
#include <iostream>
#include <utility>

using namespace ldc;

void SymbolTable::updateCurrentType(const SupportedType &update) {
  currentType = update;
}

SupportedType SymbolTable::getCurrent() { return currentType; }

bool SymbolTable::insert(const char *id) {
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
    std::cerr << "Error: Variable already declared\n\t`" << id
              << "` was already declared!";
    return false;
  }
  return table
      .insert(std::make_pair(id, std::make_tuple(currentType, valToBeAssigned)))
      .second;
}

bool SymbolTable::checkVariableExists(const char *id) {
  auto res = table.find(id);
  if (res == table.end()) {
    std::cerr << "Error: Usage of undefined variable\n\t`" << id
              << "` does not exist!";
    return false;
  }
  return true;
}

SymbolTable::SymbolInfo SymbolTable::retrieveFromIdentifier(const char *id) {
  return table.find(id)->second;
}

void SymbolTable::dump() {
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
