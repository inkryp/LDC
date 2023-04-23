#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <variant>

namespace ldc {

enum SupportedType { INT, FLOAT, UNDEFINED };

/// TODO: Come up with a description for this
class SymbolTable {
public:
  /// Implementing a singleton for SymbolTable
  static SymbolTable& getInstance() {
    static SymbolTable instance;
    return instance;
  }

  void updateCurrentType(const SupportedType&);

  int foo(int x);

private:
  std::unordered_map<char*, std::tuple<SupportedType, std::variant<int, float>>> table;

  SupportedType currentType = UNDEFINED;
};
} // namespace ldc

#endif // SYMBOLTABLE_H
