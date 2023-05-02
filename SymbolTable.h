#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include <string>
#include <utility>
#include <variant>

namespace ldc {

enum SupportedType { INT, FLOAT, BOOL, STRING, UNDEFINED };

/// TODO: Come up with a description for this
class SymbolTable {
public:
  typedef bool UserDefined;
  typedef std::tuple<SupportedType, std::variant<int, float, bool, std::string>,
                     UserDefined, std::pair<int, int>>
      SymbolInfo;
  typedef std::map<const std::string, SymbolTable::SymbolInfo>::iterator
      SymbolLocation;

  /// Implementing a singleton for SymbolTable
  static SymbolTable &getInstance() {
    static SymbolTable instance;
    return instance;
  }

  void updateCurrentType(const SupportedType &);

  SupportedType getCurrent();

  bool insert(const char *);

  std::pair<std::map<const std::string, SymbolTable::SymbolInfo>::iterator,
            bool>
      insertTemp(SymbolInfo);

  bool checkVariableExists(const char *);

  // Probably going to have to refactor this at some point
  SymbolLocation retrieveFromIdentifier(const char *);

  void dump();

  std::vector<int>& getAmountEachType();

  std::map<const std::string, SymbolInfo>& getTable();

private:
  std::map<const std::string, SymbolInfo> table;

  SupportedType currentType = UNDEFINED;

  int cntTmp = 0;

  std::vector<int> amtEachType = {0, 0, 0, 0};
};
} // namespace ldc

#endif // SYMBOL_TABLE_H
