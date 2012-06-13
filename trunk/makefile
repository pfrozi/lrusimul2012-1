cc = gcc
flags = -Wall


all: lrusimul

lrusimul: src/main.c src/lrusimul.c src/processos.c	
	$(cc) -o bin/lrusimul src/main.c src/lrusimul.c src/processos.c $(flags)
	
clean:
	rm -rf */*o
	rm -rf */*a
	rm -rf bin/*


