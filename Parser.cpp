#include "Parser.h"
#include <iostream>

extern "C"{
  void yyerror(const char *str) {
    std::cerr << "Error: " << str << '\n';
  }
  int yywrap() {
    return 1;
  }
}
