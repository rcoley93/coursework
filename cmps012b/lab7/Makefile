#Ryan Coley
#12/10/14
#rjcoley
#1332490
#lab7
#Makefile
#Makefile for lab7
MKFILE    = Makefile

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCE   = main.c
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = hash
SOURCES   = ${CSOURCE} ${MKFILE}
WORDS     = words.txt

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
	./${EXECBIN} words.txt
	
submit:
	submit cmps12b-nojw.f14 lab7 README Makefile main.c

.PHONY: all clean spotless test
