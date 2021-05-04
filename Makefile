# Makefile

#  -std=C++11 as option to g++ commands

staticSemantics: main.o parser.o scanner.o printTree.o tree.o symbolTable.o
	g++ main.o parser.o scanner.o printTree.o tree.o symbolTable.o -o staticSemantics

main.o: main.cpp printTree.h parser.h token.h tree.h node.h
	g++ -c -Wall main.cpp

parser.o: parser.cpp parser.h token.h table.h tree.h node.h
	g++ -c -Wall parser.cpp

scanner.o: scanner.cpp scanner.h token.h table.h
	g++ -c -Wall scanner.cpp

printTree.o: printTree.cpp printTree.h node.h tree.h symbolTable.h
	g++ -c -Wall printTree.cpp

tree.o: tree.cpp tree.h
	g++ -c -Wall tree.cpp

symbolTable.o: symbolTable.cpp symbolTable.h
	g++ -c -Wall symbolTable.cpp