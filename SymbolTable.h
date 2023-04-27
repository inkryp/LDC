#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include <string>
#include <variant>

namespace ldc {

enum SupportedType { INT, FLOAT, UNDEFINED };

/// TODO: Come up with a description for this
class SymbolTable {
public:
  typedef bool UserDefined;
  typedef std::tuple<SupportedType, std::variant<int, float>, UserDefined>
      SymbolInfo;

  /// Implementing a singleton for SymbolTable
  static SymbolTable &getInstance() {
    static SymbolTable instance;
    return instance;
  }

  void updateCurrentType(const SupportedType &);

  SupportedType getCurrent();

  bool insert(const char *);

  bool insertTemp(SymbolInfo);

  bool checkVariableExists(const char *);

  // Probably going to have to refactor this at some point
  SymbolInfo retrieveFromIdentifier(const char *);

  void dump();

private:
  std::map<const std::string, SymbolInfo> table;

  SupportedType currentType = UNDEFINED;

  int cntTmp = 0;
};
} // namespace ldc

#endif // SYMBOL_TABLE_H
