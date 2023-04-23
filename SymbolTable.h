#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

namespace ldc {

/// TODO: Come up with a description for this
class SymbolTable {
public:
  /// Implementing a singleton for SymbolTable
  static SymbolTable& getInstance() {
    static SymbolTable instance;
    return instance;
  }

  int foo(int x);

private:
};
} // namespace ldc

#endif // SYMBOLTABLE_H
