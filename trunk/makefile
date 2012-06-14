cc = gcc
flags = -Wall


all: lrusimul

lrusimul: src/main.c src/lrusimul.c src/processos.c	
	$(cc) -o bin/lrusimul src/processos.c src/lrusimul.c src/main.c $(flags)
	
clean:
	rm -rf */*o
	rm -rf bin/*