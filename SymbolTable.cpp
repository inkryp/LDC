#include "SymbolTable.h"
#include <iostream>
#include <string>
#include <utility>

using namespace ldc;

void SymbolTable::updateCurrentType(const SupportedType &update) {
  currentType = update;
}

SupportedType SymbolTable::getCurrent() { return currentType; }

bool SymbolTable::insert(const char *id) {
  std::variant<int, float, bool, std::string> valToBeAssigned;
  switch (currentType) {
  case INT:
    valToBeAssigned = int();
    break;
  case FLOAT:
    valToBeAssigned = float();
    break;
  case BOOL:
    valToBeAssigned = bool();
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
      .insert(std::make_pair(
          id, std::make_tuple(currentType, valToBeAssigned, true)))
      .second;
}

std::pair<std::map<const std::string, SymbolTable::SymbolInfo>::iterator, bool>
SymbolTable::insertTemp(SymbolTable::SymbolInfo tmp) {
  return table.insert({"_tmp_" + std::to_string(cntTmp++), tmp});
}

bool SymbolTable::checkVariableExists(const char *id) {
  auto res = table.find(id);
  if (res == table.end()) {
    std::cerr << "Error: Usage of undefined variable\n\t`" << id
              << "` does not exist!\n";
    return false;
  }
  return true;
}

SymbolTable::SymbolLocation
SymbolTable::retrieveFromIdentifier(const char *id) {
  return table.find(id);
}

void SymbolTable::dump() {
  std::cout << "Printing all values:\n";
  for (auto &[key, val] : table) {
    auto hereType = std::get<0>(val);
    std::cout << key << ' ' << std::get<0>(val) << ' ';
    if (hereType == INT) {
      std::cout << std::get<int>(std::get<1>(val)) << '\n';
    } else if (hereType == FLOAT) {
      std::cout << std::get<float>(std::get<1>(val)) << '\n';
    } else if (hereType == BOOL) {
      std::cout << std::get<bool>(std::get<1>(val)) << '\n';
    } else {
      std::cout << std::get<std::string>(std::get<1>(val)) << '\n';
    }
  }
}
