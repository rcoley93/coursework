#Ryan Coley
#rjcoley
#CMPS12B
#10/22/14
#makefile
#compiles BusinessSearch
#No Special Instructions or notes
JAVASRC = BusinessSearch.java
SOURCES = README Makefile ${JAVASRC}
MAINCLASS = BusinessSearch
CLASSES = BusinessSearch.class Record.class
JARFILE = BusinessSearch
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
