ldc:
	lex -o Lexer.c Lexer.l
	yacc -d Parser.y -o LittleDuckCompiler.cpp
	gcc -c Lexer.c -o Lexer.o
	g++ -c Parser.cpp -o Parser.o
	g++ Lexer.o Parser.o LittleDuckCompiler.cpp -o ldc.out
