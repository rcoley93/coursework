#------------------------------------------------------------------------------
# Ryan Coley
# rjcoley
# pa3
# Makefile for CMPS 101 pa3 
# Compiles all .java files in the current directory and creates an executable
# jar file called Sparse.  See the following for a short description of makefiles
#------------------------------------------------------------------------------ 

MAINCLASS  = Sparse
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 

all: $(JARFILE)
	
$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)

submit:
	submit cmps101-pt.w15 pa3 $(SOURCES)
