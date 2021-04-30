.DEFAULT_GOAL := check

.PHONY: clean

clean : 
	rm -rf build

build :
	mkdir -p build

build/analyseur_lex.o : lib/analyseur_lex.c lib/analyseur_lex.h | build
	gcc -Wall -Werror -pedantic --debug -c lib/analyseur_lex.c -I ./lib -o build/analyseur_lex.o

build/test.o : main.c | build
	gcc -Wall -Werror -pedantic --debug -c main.c -I ./lib -o build/test.o

build/test : build/test.o build/analyseur_lex.o | build
	gcc build/test.o build/analyseur_lex.o -o build/test

check : build/test
	./build/test