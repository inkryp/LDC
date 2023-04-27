%{
#include "ExpressionChecker.h"
#include "Parser.h"
#include "SymbolTable.h"

auto &symbol_table = ldc::SymbolTable::getInstance();
auto &expression_checker = ldc::ExpressionChecker::getInstance();
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
  cuerpo program_factor_holder
  | vars cuerpo program_factor_holder

program_factor_holder:
  TOK_END { symbol_table.dump(); } 

vars:
  TOK_VAR vars_gen

vars_gen:
  tipo TOK_COLON vars_inner TOK_SEMICOLON vars_loop

vars_loop:
  vars_gen
  | /*epsilon*/

vars_inner:
  TOK_IDENTIFIER vars_inner_placeholder {
    if (!symbol_table.insert($<str>$)) YYABORT;
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
  TOK_IDENTIFIER TOK_ASSIGNMENT asigna_placeholder { if (!symbol_table.checkVariableExists($<str>$)) YYABORT; }

asigna_placeholder:
  expresion asigna_placeholder_variable_matches {
    // TODO: Implement this member function
    // expression_checker.check();
  }

asigna_placeholder_variable_matches:
  TOK_SEMICOLON

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
  TOK_IDENTIFIER    { expression_checker.setCurrentOperand($<str>$); }
  | TOK_CONST_INT   { expression_checker.setCurrentOperand($<integer>$); }
  | TOK_CONST_FLOAT { expression_checker.setCurrentOperand($<floating_point>$); }

%%

int main() {
  return yyparse();
}
