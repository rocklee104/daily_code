CC=gcc

all: clean main.o vt.o
	${CC} -o main main.o vt.o -I .

vt.o:
	${CC} -o $@ -c vt.c -I .

clean:
	rm -rf main *.o
