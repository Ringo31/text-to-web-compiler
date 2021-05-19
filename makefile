.DEFAULT_GOAL := check

.PHONY: clean

clean : 
	rm -rf build

build :
	mkdir -p build

build/analyseur_lex.o : lib/analyseur_lex.c lib/analyseur_lex.h | build
	gcc -Wall -Werror -pedantic --debug -c lib/analyseur_lex.c -I ./lib -o build/analyseur_lex.o

build/analyseur_synt.o : lib/analyseur_synt.c lib/analyseur_synt.h | build
	gcc -Wall -Werror -pedantic --debug -c lib/analyseur_synt.c -I ./lib -o build/analyseur_synt.o

build/test.o : main.c | build
	gcc -Wall -Werror -pedantic --debug -c main.c -I ./lib -o build/test.o

build/test : build/test.o build/analyseur_lex.o build/analyseur_synt.o | build
	gcc build/test.o build/analyseur_lex.o build/analyseur_synt.o -o build/test

check : build/test
	./build/test