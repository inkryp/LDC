%{
#include <stdio.h>
%}

OPEN_PARENTHESIS "("
CLOSED_PARENTHESIS ")"

%%
prog                          printf("TOK_PROG\n");
end                           printf("TOK_END\n");

var                           printf("TOK_VAR\n");
si                            printf("TOK_IF\n");
sino                          printf("TOK_ELSE\n");
mientras                      printf("TOK_WHILE\n");
print                         printf("TOK_PRINT\n");

=                             printf("TOK_ASSIGNMENT\n");
;                             printf("TOK_SEMICOLON\n");
:                             printf("TOK_COLON\n");
,                             printf("TOK_COMMA\n");

int                           printf("TOK_INT\n");
float                         printf("TOK_FLOAT\n");

{OPEN_PARENTHESIS}            printf("TOK_OPEN_PARENTHESIS\n");
{CLOSED_PARENTHESIS}          printf("TOK_CLOSED_PARENTHESIS\n");

\[                            printf("TOK_OPEN_BRACKET\n");
\]                            printf("TOK_CLOSED_BRACKET\n");

\{                            printf("TOK_OPEN_BRACE\n");
\}                            printf("TOK_CLOSED_BRACE\n");

\+                            printf("TOK_PLUS\n");
\-                            printf("TOK_MINUS\n");
\*                            printf("TOK_MULTIPLICATION\n");
\/                            printf("TOK_DIVISION\n");

\<\>                          printf("TOK_OTHER_OPERATOR\n");
\<                            printf("TOK_LESS_THAN\n");
\>                            printf("TOK_GREATER_THAN\n");

[[:lower:]][[:alnum:]_]*      printf("TOK_IDENTIFIER\n");
\".*\"                        printf("TOK_CONST_STRING\n");
[[:digit:]]+                  printf("TOK_CONST_INT\n");
[[:digit:]]+\.[[:digit:]]*    printf("TOK_CONST_FLOAT\n");

\n                            /* ignore whitespace */
[ \t]+                        /* ignore whitespace */

%%
