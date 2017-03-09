CC=gcc
LDFLAGS= -I .

OBJS = main.o vt.o  bitmap.o term.o thread.o

all: $(OBJS)
	${CC} -o main $(OBJS) $(LDFLAGS)

.PHONY:clean

clean:
	rm -rf main *.o
