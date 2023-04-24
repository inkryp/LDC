%{
#include "Parser.h"
#include "SymbolTable.h"

#include <iostream>
auto& symbol_table = ldc::SymbolTable::getInstance();
%}

%union {
  int integer;
  float floating_point;
  char *str;
}

%token TOK_PROG TOK_END TOK_VAR TOK_IF TOK_ELSE TOK_WHILE TOK_PRINT TOK_ASSIGNMENT TOK_SEMICOLON TOK_COLON TOK_COMMA TOK_INT TOK_FLOAT TOK_OPEN_PARENTHESIS TOK_CLOSED_PARENTHESIS TOK_OPEN_BRACKET TOK_CLOSED_BRACKET TOK_OPEN_BRACE TOK_CLOSED_BRACE TOK_PLUS TOK_MINUS TOK_MULTIPLICATION TOK_DIVISION TOK_OTHER_OPERATOR TOK_LESS_THAN TOK_GREATER_THAN TOK_IDENTIFIER TOK_CONST_STRING TOK_CONST_INT TOK_CONST_FLOAT

%%
program:
  TOK_PROG TOK_IDENTIFIER TOK_SEMICOLON program_factor

program_factor:
  cuerpo TOK_END { symbol_table.printTable(); }
  | vars cuerpo TOK_END { symbol_table.printTable(); }

vars:
  TOK_VAR vars_gen

vars_gen:
  tipo TOK_COLON vars_inner TOK_SEMICOLON vars_loop

vars_loop:
  vars_gen
  | /*epsilon*/

vars_inner:
  TOK_IDENTIFIER vars_inner_placeholder {
    symbol_table.insert($<str>$);
  }

vars_inner_placeholder:
  vars_inner_loop

vars_inner_loop:
  TOK_COMMA vars_inner
  | /*epsilon*/

tipo:
  TOK_INT         { symbol_table.updateCurrentType(ldc::INT); }
  | TOK_FLOAT     { symbol_table.updateCurrentType(ldc::FLOAT); }

cuerpo:
  TOK_OPEN_BRACKET cuerpo_w TOK_CLOSED_BRACKET

cuerpo_w:
  estatuto cuerpo_w
  | /*epsilon*/

estatuto:
  asigna
  | condicion
  | ciclo
  | escritura

asigna:
  TOK_IDENTIFIER TOK_ASSIGNMENT asigna_placeholder { symbol_table.checkVariableExists($<str>$); }

asigna_placeholder:
  expresion TOK_SEMICOLON

condicion:
  TOK_IF TOK_OPEN_PARENTHESIS expresion TOK_CLOSED_PARENTHESIS cuerpo condicion_aux TOK_SEMICOLON

condicion_aux:
  /*epsilon*/
  | TOK_ELSE cuerpo

ciclo:
  TOK_WHILE TOK_OPEN_PARENTHESIS expresion TOK_CLOSED_PARENTHESIS cuerpo TOK_SEMICOLON

escritura:
  TOK_PRINT TOK_OPEN_PARENTHESIS escritura_aux TOK_CLOSED_PARENTHESIS TOK_SEMICOLON

escritura_aux:
  escritura_inner escritura_find

escritura_find:
  /*epsilon*/
  | TOK_COMMA escritura_aux

escritura_inner:
  expresion
  | TOK_CONST_STRING

expresion:
  exp expresion_comp

expresion_comp:
  /*epsilon*/
  | expresion_operator_select exp

expresion_operator_select:
  TOK_GREATER_THAN
  | TOK_LESS_THAN
  | TOK_OTHER_OPERATOR

exp:
  termino exp_aux

exp_aux:
  /*epsilon*/
  | exp_operator exp

exp_operator:
  TOK_PLUS
  | TOK_MINUS

termino:
  factor termino_aux

termino_aux:
  /*epsilon*/
  | termino_operator termino

termino_operator:
  TOK_MULTIPLICATION
  | TOK_DIVISION

factor:
  TOK_OPEN_PARENTHESIS expresion TOK_CLOSED_PARENTHESIS
  | var_cte
  | factor_cte_sign var_cte

factor_cte_sign:
  TOK_PLUS
  | TOK_MINUS

var_cte:
  TOK_IDENTIFIER { std::cout << $<str>$ << '\n'; }
  | TOK_CONST_INT { std::cout << $<integer>$ << '\t' << symbol_table.foo($<integer>$) << '\n'; }
  | TOK_CONST_FLOAT { std::cout << $<floating_point>$ << '\n'; }

%%

int main() {
  return yyparse();
}
