#Ryan Coley
#12/12/14
#rjcoley
#1332490
#lab7
#Makefile
#Makefile for heap.c

MKFILE    = Makefile

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCE   = heap.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = heap
SOURCES   = ${CSOURCE} ${MKFILE}

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	${GCC} -c $<

clean :
	rm -f ${OBJECTS} core

spotless : clean
	rm -f ${EXECBIN}

test : ${EXECBIN}
	./${EXECBIN} 10 test.txt
	
submit:	
	submit cmps12b-nojw.f14 lab8 README Makefile heap.c

.PHONY: all clean spotless test
