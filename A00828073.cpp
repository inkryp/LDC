#include <iostream>
#include "A00828073.h"

extern "C"{
  void yyerror(const char *str) {
    std::cerr << "Error: " << str << '\n';
  }
  int yywrap() {
    return 1;
  }
}
