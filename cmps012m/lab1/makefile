#Ryan Coley
#rjcoley
#CMPS12B
#10/05/14
#makefile
#compiles myHello
#No Special Instructions or notes
JAVASRC = hello2.java hello.java
SOURCES = README Makefile ${JAVASRC}
MAINCLASS = hello2
CLASSES = hello2.class hello.class
JARFILE = myHello
JARCLASSES = ${CLASSES}

all: ${JARFILE}

${JARFILE}: ${CLASSES}
	echo "Main-class: ${MAINCLASS}" > Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	rm Manifest
	chmod +x ${JARFILE}

${CLASSES}: ${JAVASRC}
	javac -Xlint ${JAVASRC}

clean:
	rm ${CLASSES} ${JARFILE}

.PHONY: clean all
