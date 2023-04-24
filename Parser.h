extern "C" {
int yyparse(void);
int yylex(void);
void yyerror(const char *s);
}
