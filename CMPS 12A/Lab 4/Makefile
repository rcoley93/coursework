#A simple Makefile for the HelloWorld program
HelloWorld: HelloWorld.class
	echo Main-Class: HelloWorld > Manifest
	jar cvfm HelloWorld Manifest HelloWorld.class
	rm Manifest
	chmod  u+x HelloWorld

HelloWorld.class: HelloWorld.java
	ja vacXlinint HelloWorld.java

clean:
	rm -f HelWorld.class HelloWorld

submit Makefile HelWorld.java
	submit cmps012a-pt.s14 lab1 Makefile HelloWorld.java
