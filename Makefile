# Name: Hudson Shykowski & Dale Richmond Naviza
# ID : 1520045 & 1534579
# CMPUT 275, Winter 2019
# Final Assignment: P- programming language

CC=@g++
CFLAGS=-c -std=c++11
LFLAGS=
OBJS= main main.o transpiler.o lexer.o transpiler.o grammar.o program


main: main.o grammar.o transpiler.o lexer.o
	$(CC) main.o lexer.o transpiler.o grammar.o -o main $(LFLAGS)

main.o: grammar.o transpiler.o lexer.o
	$(CC) main.cpp $(CFLAGS) -o main.o

grammar.o: transpiler.h	lexer.h grammar.cpp grammar.h
	$(CC) grammar.cpp $(CFLAGS) -o grammar.o

transpiler.o: transpiler.cpp transpiler.h lexer.h
	$(CC) transpiler.cpp $(CFLAGS) -o transpiler.o

lexer.o: lexer.cpp lexer.h
	$(CC) lexer.cpp $(CFLAGS) -o lexer.o

clean:
	@rm -rf $(OBJS)
