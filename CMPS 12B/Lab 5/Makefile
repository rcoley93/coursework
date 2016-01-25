#Ryan Coley
#1332490
#rjcoley
#CMPS12B
#11/17/14
#Makefile
#makefile for list.c
CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wfatal-errors -g
OBJS = list.o
OUTPUT = list
HEADERS = 

${OUTPUT}: ${OBJS}
	${CC} $< -o ${OUTPUT}

%.o: %.c ${HEADERS}
	${CC} -c ${CFLAGS} $<

clean:
	rm -f *.o

spotless: clean
	rm -f ${OUTPUT}

test: ${OUTPUT}
	valgrind -v ./${OUTPUT}

submit:
	submit cmps12b-nojw.f14 lab5 README BUGS Makefile list.c

.PHONY: clean spotless test submit

