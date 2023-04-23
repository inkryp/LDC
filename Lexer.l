%{
#include "LittleDuckCompiler.hpp"
%}

OPEN_PARENTHESIS "("
CLOSED_PARENTHESIS ")"

%%
prog                          return TOK_PROG;
end                           return TOK_END;

var                           return TOK_VAR;
si                            return TOK_IF;
sino                          return TOK_ELSE;
mientras                      return TOK_WHILE;
print                         return TOK_PRINT;

=                             return TOK_ASSIGNMENT;
;                             return TOK_SEMICOLON;
:                             return TOK_COLON;
,                             return TOK_COMMA;

int                           return TOK_INT;
float                         return TOK_FLOAT;

{OPEN_PARENTHESIS}            return TOK_OPEN_PARENTHESIS;
{CLOSED_PARENTHESIS}          return TOK_CLOSED_PARENTHESIS;

\[                            return TOK_OPEN_BRACKET;
\]                            return TOK_CLOSED_BRACKET;

\{                            return TOK_OPEN_BRACE;
\}                            return TOK_CLOSED_BRACE;

\+                            return TOK_PLUS;
\-                            return TOK_MINUS;
\*                            return TOK_MULTIPLICATION;
\/                            return TOK_DIVISION;

\<\>                          return TOK_OTHER_OPERATOR;
\<                            return TOK_LESS_THAN;
\>                            return TOK_GREATER_THAN;

[[:lower:]][[:alnum:]_]*      { yylval.str = strdup(yytext); return TOK_IDENTIFIER; }
\".*\"                        { yylval.str = strdup(yytext); return TOK_CONST_STRING; }
[[:digit:]]+                  { yylval.integer = atoi(yytext); return TOK_CONST_INT; }
[[:digit:]]+\.[[:digit:]]*    { yylval.floating_point = atof(yytext); return TOK_CONST_FLOAT; }

\n                            /* ignore whitespace */
[ \t]+                        /* ignore whitespace */

%%
