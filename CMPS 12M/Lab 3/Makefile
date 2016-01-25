#Ryan Coley
#1332490
#rjcoley
#CMPS12M
#10/28/14
# Makefile
# Build a class and do unit tests
#No Special Instructions
JAVASRC = Calc.java CalcTest.java
SOURCES = Makefile.unit ${JAVASRC}
CLASSES = Calc.class CalcTest.class
TESTCLASS = CalcTest
CLASSPATH = "junit-4.12-beta-1.jar:hamcrest-core-1.3.jar:."

all: ${CLASSES}

${CLASSES}: ${JAVASRC}
	javac -Xlint -cp ${CLASSPATH} ${JAVASRC}

clean:
	rm ${CLASSES}

test: ${CLASSES}
	java -cp ${CLASSPATH} org.junit.runner.JUnitCore ${TESTCLASS}

.PHONY: clean all test
