#Ryan Coley
#1332490
#rjcoley
#CMPS12B
#10/14/14
#makefile
#compiles greet.java and greetings.java
#No Special Instructions or notes

runGreet: Greet
	Greet

Greet: greet.class
	echo Main-class: greet > Manifest
	jar cvfm Greet Manifest greet.class
	rm Manifest
	chmod +x Greet
	
greet.class: greet.java
	javac -Xlint greet.java
	
runGreetings: Greetings
	Greetings

Greetings: greetings.class
	echo Main-class: greetings > Manifest
	jar cvfm Greetings Manifest greetings.class
	rm Manifest
	chmod +x Greetings
	
greetings.class: greetings.java
	javac -Xlint greetings.java
	
clean:
	rm -f greet.class greetings.class Greet Greetings
	
.PHONY: clean runGreet runGreetings
