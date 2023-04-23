ldc:
	lex -o Lexer.c Lexer.l
	yacc -d Parser.y -o LittleDuckCompiler.cpp
	gcc -c Lexer.c -o Lexer.o
	g++ -std=c++11 -Wall -c Parser.cpp -o Parser.o
	g++ -std=c++11 -Wall -c SymbolTable.cpp -o SymbolTable.o
	g++ -std=c++11 -Wall Lexer.o Parser.o SymbolTable.o LittleDuckCompiler.cpp -o ldc.out
