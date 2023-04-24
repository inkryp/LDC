#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <variant>
#include <string>

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

  SupportedType getCurrent();

  void insert(const char*);

  void checkVariableExists(const char *);

  void printTable();

private:
  std::map<const std::string, std::tuple<SupportedType, std::variant<int, float>>> table;

  SupportedType currentType = UNDEFINED;
};
} // namespace ldc

#endif // SYMBOLTABLE_H
