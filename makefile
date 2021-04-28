.DEFAULT_GOAL := check

.PHONY: clean

clean : 
	rm -rf build

build :
	mkdir -p build

build/test.o : main.c | build
	gcc -Wall -Werror -pedantic --debug -c main.c -I ./lib -o build/test.o

build/test : build/test.o | build
	gcc build/test.o -o build/test

check : build/test
	./build/test