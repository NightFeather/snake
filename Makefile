
SRCDIR="src/"
INCLUDEDIR="include/"
BUILDDIR="build/"

default: main

main: build/main.o
	gcc -I${INCLUDEDIR} build/main.o -o main

build/main.o: src/main.c
	gcc -I${INCLUDEDIR} -c src/main.c -o build/main.o

clean:
	rm build/* main
