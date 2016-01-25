MKFILE    = Makefile

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCE   = test.c
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
	./${EXECBIN}

.PHONY: all clean spotless test
