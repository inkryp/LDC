%{
#include "CodeGenerator.h"
#include "ExpressionChecker.h"
#include "Parser.h"
#include "SymbolTable.h"
#include <variant>

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

auto &symbol_table = ldc::SymbolTable::getInstance();
auto &expression_checker = ldc::ExpressionChecker::getInstance();
auto &code_generator = ldc::CodeGenerator::getInstance();
//auto &memory_manager = ldc::CodeExecutor::getInstance();
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
  TOK_END {
    //symbol_table.dump();
    //code_generator.dump();
    int idx = 0;
    auto quads = code_generator.getQuadruples();
    // Execute the code itself
    while (idx < quads.size()) {
      int new_idx = -1;
      if (std::holds_alternative<ldc::Quadruple::BinaryOp>(quads[idx].op)) {
        auto op = std::get<ldc::Quadruple::BinaryOp>(quads[idx].op);
        assert(quads[idx].left && quads[idx].right && quads[idx].result && "All this values should exist");
        auto left = std::get<ldc::SymbolTable::SymbolLocation>(*(quads[idx].left)),
             right = std::get<ldc::SymbolTable::SymbolLocation>(*(quads[idx].right)),
             result = std::get<ldc::SymbolTable::SymbolLocation>(*(quads[idx].result));
        switch (op) {
          case ldc::Quadruple::BinaryOp::ADDITION:
            std::visit(overload{
              [](int& left, int& right, auto&& result) { result = left + right; },
              [](int& left, float& right, auto&& result) { result = left + right; },
              [](float& left, int& right, auto&& result) { result = left + right; },
              [](float& left, float& right, auto&& result) { result = left + right; },
              [](auto&& left, auto&& right, auto&& result) {
                std::cerr << "Error: This case should not occurr\n";
                assert(0);
              }
            }, std::get<1>(left->second), std::get<1>(right->second), std::get<1>(result->second));
            break;
          case ldc::Quadruple::BinaryOp::SUBSTRACTION:
            std::visit(overload{
              [](int& left, int& right, auto&& result) { result = left - right; },
              [](int& left, float& right, auto&& result) { result = left - right; },
              [](float& left, int& right, auto&& result) { result = left - right; },
              [](float& left, float& right, auto&& result) { result = left - right; },
              [](auto&& left, auto&& right, auto&& result) {
                std::cerr << "Error: This case should not occurr\n";
                assert(0);
              }
            }, std::get<1>(left->second), std::get<1>(right->second), std::get<1>(result->second));
            break;
          case ldc::Quadruple::BinaryOp::MULTIPLICATION:
            std::visit(overload{
              [](int& left, int& right, auto&& result) { result = left * right; },
              [](int& left, float& right, auto&& result) { result = left * right; },
              [](float& left, int& right, auto&& result) { result = left * right; },
              [](float& left, float& right, auto&& result) { result = left * right; },
              [](auto&& left, auto&& right, auto&& result) {
                std::cerr << "Error: This case should not occurr\n";
                assert(0);
              }
            }, std::get<1>(left->second), std::get<1>(right->second), std::get<1>(result->second));
            break;
          case ldc::Quadruple::BinaryOp::DIVISION:
            std::visit(overload{
              [](int& left, int& right, auto&& result) { result = left / right; },
              [](int& left, float& right, auto&& result) { result = left / right; },
              [](float& left, int& right, auto&& result) { result = left / right; },
              [](float& left, float& right, auto&& result) { result = left / right; },
              [](auto&& left, auto&& right, auto&& result) {
                std::cerr << "Error: This case should not occurr\n";
                assert(0);
              }
            }, std::get<1>(left->second), std::get<1>(right->second), std::get<1>(result->second));
            break;
          case ldc::Quadruple::BinaryOp::LESS_THAN:
            std::visit(overload{
              [](int& left, int& right, auto&& result) { result = (left < right); },
              [](int& left, float& right, auto&& result) { result = (left < right); },
              [](float& left, int& right, auto&& result) { result = (left < right); },
              [](float& left, float& right, auto&& result) { result = (left < right); },
              [](bool& left, bool& right, auto&& result) { result = (left < right); },
              [](auto&& left, auto&& right, auto&& result) {
                std::cerr << "Error: This case should not occurr\n";
                assert(0);
              }
            }, std::get<1>(left->second), std::get<1>(right->second), std::get<1>(result->second));
            break;
          case ldc::Quadruple::BinaryOp::GREATER_THAN:
            std::visit(overload{
              [](int& left, int& right, auto&& result) { result = (left > right); },
              [](int& left, float& right, auto&& result) { result = (left > right); },
              [](float& left, int& right, auto&& result) { result = (left > right); },
              [](float& left, float& right, auto&& result) { result = (left > right); },
              [](bool& left, bool& right, auto&& result) { result = (left > right); },
              [](auto&& left, auto&& right, auto&& result) {
                std::cerr << "Error: This case should not occurr\n";
                assert(0);
              }
            }, std::get<1>(left->second), std::get<1>(right->second), std::get<1>(result->second));
            break;
          case ldc::Quadruple::BinaryOp::OTHER_THAN:
            std::visit(overload{
              [](int& left, int& right, auto&& result) { result = (left != right); },
              [](int& left, float& right, auto&& result) { result = (left != right); },
              [](float& left, int& right, auto&& result) { result = (left != right); },
              [](float& left, float& right, auto&& result) { result = (left != right); },
              [](bool& left, bool& right, auto&& result) { result = (left != right); },
              [](auto&& left, auto&& right, auto&& result) {
                std::cerr << "Error: This case should not occurr\n";
                assert(0);
              }
            }, std::get<1>(left->second), std::get<1>(right->second), std::get<1>(result->second));
            break;
          default:
            std::cerr << "Runtime error: Shouldn't get here\n";
            YYABORT;
        }
      } else {
        auto op = std::get<ldc::Quadruple::Op>(quads[idx].op);
        ldc::SymbolTable::SymbolLocation left, right, result;
        int pos;
        switch (op) {
          case ldc::Quadruple::Op::ASSIGN:
            assert(quads[idx].left && !quads[idx].right && quads[idx].result && "All this values should match");
            left = std::get<ldc::SymbolTable::SymbolLocation>(*(quads[idx].left));
            result = std::get<ldc::SymbolTable::SymbolLocation>(*(quads[idx].result));
            std::get<1>(result->second) = std::get<1>(left->second);
            break;
          case ldc::Quadruple::Op::GOTO:
            assert(!quads[idx].left && !quads[idx].right && quads[idx].result && "All this values should match");
            pos = std::get<int>(*(quads[idx].result));
            new_idx = pos;
            break;
          case ldc::Quadruple::Op::GOTOF:
            assert(quads[idx].left && !quads[idx].right && quads[idx].result && "All this values should match");
            left = std::get<ldc::SymbolTable::SymbolLocation>(*(quads[idx].left));
            pos = std::get<int>(*(quads[idx].result));
            if (!std::get<bool>(std::get<1>(left->second))) {
              new_idx = pos;
            }
            break;
          case ldc::Quadruple::Op::PRINT:
            assert(!quads[idx].left && !quads[idx].right && quads[idx].result && "All this values should match");
            result = std::get<ldc::SymbolTable::SymbolLocation>(*(quads[idx].result));
            if (auto *val = std::get_if<int>(&(std::get<1>(result->second)))) {
              std::cout << *val << '\n';
            } else if (auto *val = std::get_if<float>(&(std::get<1>(result->second)))) {
              std::cout << *val << '\n';
            } else if (auto *val = std::get_if<bool>(&(std::get<1>(result->second)))) {
              std::cout << *val << '\n';
            } else if (auto *val = std::get_if<std::string>(&(std::get<1>(result->second)))) {
              std::cout << *val << '\n';
            }
            break;
          default:
            std::cerr << "Runtime error: Shouldn't get here\n";
            YYABORT;
        }
      }
      if (new_idx == -1) {
        ++idx;
      } else {
        idx = new_idx;
      }
    }
  } 

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
  TOK_IDENTIFIER TOK_ASSIGNMENT {
    // Thank you...
    // https://www.ibm.com/docs/en/zos/2.3.0?topic=topics-rules-multiple-actions
    if (!symbol_table.checkVariableExists($<str>1)) YYABORT;
    expression_checker.setCurrentReturnValue($<str>1);
  } expresion { if (!expression_checker.check()) YYABORT; } TOK_SEMICOLON

condicion:
  TOK_IF TOK_OPEN_PARENTHESIS expresion {
    if (!expression_checker.checkBoolExpression()) YYABORT;
    if (!expression_checker.insertGotoFalse()) YYABORT;
  } TOK_CLOSED_PARENTHESIS cuerpo condicion_aux TOK_SEMICOLON {
    if (!code_generator.fillLastPendingJump()) YYABORT;
  }

condicion_aux:
  /*epsilon*/
  | TOK_ELSE {
    code_generator.insertQuad(
      {ldc::Quadruple::Op::GOTO, {}, {}, {}});
    if (!code_generator.fillLastPendingJump()) YYABORT;
    code_generator.pushbackToPendingJumps();
  } cuerpo

ciclo:
  TOK_WHILE {
    code_generator.pushbackToPendingJumps(0);
  } TOK_OPEN_PARENTHESIS expresion {
    if (!expression_checker.checkBoolExpression()) YYABORT;
    if (!expression_checker.insertGotoFalse()) YYABORT;
  } TOK_CLOSED_PARENTHESIS cuerpo TOK_SEMICOLON {
    if (!code_generator.fillLastPendingJump(-1)) YYABORT;
    auto returnDestination = code_generator.popLastPendingJump();
    code_generator.insertQuad(
      {ldc::Quadruple::Op::GOTO, {}, {}, returnDestination});
  }

escritura:
  TOK_PRINT TOK_OPEN_PARENTHESIS escritura_aux TOK_CLOSED_PARENTHESIS TOK_SEMICOLON

escritura_aux:
  escritura_inner escritura_find

escritura_find:
  /*epsilon*/
  | TOK_COMMA escritura_aux

escritura_inner:
  expresion {
    auto var = expression_checker.getCurrentOperand();
    code_generator.insertQuad(
      {ldc::Quadruple::Op::PRINT, {}, {}, var});
  }
  | TOK_CONST_STRING {
    // TODO: Probably shouldn't have this kind of spaghetti code but whatever
    auto &amtEachType = ldc::SymbolTable::getInstance().getAmountEachType();
    std::pair<int, int> pos = {3, amtEachType[3]++};
    auto currentString = ldc::SymbolTable::SymbolInfo(ldc::SupportedType::STRING, $<str>1, false, pos);
    auto result = symbol_table.insertTemp(currentString);
    if (!result.second) {
      assert(0 && "There was an error when inserting a temporary value");
    }
    code_generator.insertQuad(
      {ldc::Quadruple::Op::PRINT, {}, {}, result.first});
  }

expresion:
  exp expresion_comp

expresion_comp:
  /*epsilon*/
  | expresion_operator_select exp {
    auto op = expression_checker.peekOperator();
    if (op && (op == ldc::Quadruple::BinaryOp::LESS_THAN || op == ldc::Quadruple::BinaryOp::GREATER_THAN || op == ldc::Quadruple::OTHER_THAN)) {
      if (!expression_checker.executeOperation()) {
        YYABORT;
      }
    }  
  }

expresion_operator_select:
  TOK_GREATER_THAN { expression_checker.insertOperator(ldc::Quadruple::GREATER_THAN); }
  | TOK_LESS_THAN { expression_checker.insertOperator(ldc::Quadruple::LESS_THAN); }
  | TOK_OTHER_OPERATOR { expression_checker.insertOperator(ldc::Quadruple::OTHER_THAN); }

exp:
  termino {
    auto op = expression_checker.peekOperator();
    if (op && (op == ldc::Quadruple::BinaryOp::ADDITION || op == ldc::Quadruple::BinaryOp::SUBSTRACTION)) {
      if (!expression_checker.executeOperation()) {
        YYABORT;
      }
    }  
  } exp_aux

exp_aux:
  /*epsilon*/
  | exp_operator exp

exp_operator:
  TOK_PLUS { expression_checker.insertOperator(ldc::Quadruple::ADDITION); }
  | TOK_MINUS { expression_checker.insertOperator(ldc::Quadruple::SUBSTRACTION); }

termino:
  factor {
    auto op = expression_checker.peekOperator();
    if (op && (op == ldc::Quadruple::BinaryOp::MULTIPLICATION || op == ldc::Quadruple::BinaryOp::DIVISION)) {
      if (!expression_checker.executeOperation()) {
        YYABORT;
      }
    }  
  } termino_aux 

termino_aux:
  /*epsilon*/
  | termino_operator termino

termino_operator:
  TOK_MULTIPLICATION { expression_checker.insertOperator(ldc::Quadruple::MULTIPLICATION); }
  | TOK_DIVISION { expression_checker.insertOperator(ldc::Quadruple::DIVISION); }

factor:
  TOK_OPEN_PARENTHESIS { expression_checker.insertOperator(ldc::Quadruple::PLACEHOLDER); } factor_placeholder 
  | var_cte { expression_checker.insertCurrentOperand(); }
  | factor_cte_sign var_cte { /* TODO: Implement this place */ }

factor_placeholder:
  expresion TOK_CLOSED_PARENTHESIS { if (!expression_checker.removeOperatorPlaceholder()) YYABORT; }

factor_cte_sign:
  TOK_PLUS
  | TOK_MINUS

var_cte:
  TOK_IDENTIFIER    { if (!symbol_table.checkVariableExists($<str>$)) YYABORT; expression_checker.setCurrentOperand($<str>$); }
  | TOK_CONST_INT   { expression_checker.setCurrentOperand($<integer>$); }
  | TOK_CONST_FLOAT { expression_checker.setCurrentOperand($<floating_point>$); }

%%

int main() {
  return yyparse();
}
