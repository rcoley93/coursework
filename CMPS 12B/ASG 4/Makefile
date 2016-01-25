#Ryan Coley
#12/8/14
#rjcoley
#1332490
#asg4
#Makefile
#Makefile for cyoa

JAVASRC    = cyoa.java auxlib.java queue.java description.java rooms.java
SOURCES    = ${JAVASRC} Makefile
ALLSOURCES = ${SOURCES}
MAINCLASS  = cyoa
CLASSES    = ${patsubst %.java, %.class, ${JAVASRC}}

all: ${CLASSES}

%.class: %.java
	javac -Xlint ${MAINCLASS}.java

clean:
	rm -f *.class

test: all
	java cyoa demo.adventure

submit:
	submit cmps12b-nojw.f14 asg4 README Makefile auxlib.java cyoa.java demo.adventure queue.java description.java Design.txt

.PHONY: clean all test submit
