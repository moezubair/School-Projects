all: rsi.o execute.o
	gcc rsi.o execute.o -o rsi

rsi.o:
	gcc -c rsi.c

execute.o:
	gcc -c execute.c


clean:
	rm -rf *o rsi

