#Ryan Coley
#rjcoley
#pa2
#Makefile
#Compiles all the files for Lex

Lex: Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o: Lex.c List.h
	gcc -c -g -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o: ListClient.c List.h
	gcc -c -g -std=c99 -Wall ListClient.c

List.o: List.c List.h
	gcc -c -g -std=c99 -Wall List.c

clean:
	rm -f Lex ListClient Lex.o ListClient.o List.o
	
submit:
	submit cmps101-pt.w15 pa2 Lex.c List.h List.c ListClient.c README Makefile
 