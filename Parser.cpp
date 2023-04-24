#include "Parser.h"
#include <iostream>

extern "C" {
void yyerror(const char *str) {
  std::cerr << "Error: " << str << '\n';
  assert(0 && "Error when parsing");
}
int yywrap() { return 1; }
}
