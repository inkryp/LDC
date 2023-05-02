ldc:
	lex -o Lexer.c Lexer.l
	yacc -d Parser.y -o LittleDuckCompiler.cpp
	gcc -c Lexer.c -o Lexer.o
	g++ -std=c++17 -Wall -c Parser.cpp -o Parser.o
	g++ -std=c++17 -Wall -c SymbolTable.cpp -o SymbolTable.o
	g++ -std=c++17 -Wall -c ExpressionChecker.cpp -o ExpressionChecker.o
	g++ -std=c++17 -Wall -c CodeGenerator.cpp -o CodeGenerator.o
	g++ -std=c++17 -Wall -c MemoryManager.cpp -o MemoryManager.o
	g++ -std=c++17 -Wall Lexer.o Parser.o SymbolTable.o ExpressionChecker.o CodeGenerator.o MemoryManager.o LittleDuckCompiler.cpp -o ldc.out
