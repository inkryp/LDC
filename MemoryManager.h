#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <utility>
#include <vector>

namespace ldc {

class MemoryManager {
private:
  std::vector<std::vector<std::variant<int, float, bool, std::string>>> mem;

public:
  /// Implementing a singleton for ExpressionChecker
  static MemoryManager &getInstance() {
    static MemoryManager instance;
    return instance;
  }
  void initializeMemory();
  std::variant<int, float, bool, std::string> &
      getMemoryLocation(std::pair<int, int>);
};
} // namespace ldc

#endif // MEMORY_MANAGER_H
