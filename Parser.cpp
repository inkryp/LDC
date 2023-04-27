#include "Parser.h"
#include <iostream>

extern "C" {
void yyerror(const char *str) {
  std::cerr << "Error: " << str << '\n';
  assert(0 && "Error: File not acceptable by the grammar");
}
int yywrap() { return 1; }
}
