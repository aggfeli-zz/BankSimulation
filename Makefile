# clean
clean: rm -f *.o elegxos

# all
all: main.o Graph.o Hashtable.o
	gcc -g main.o Graph.o Hashtable.o -o elegxos

main.o: main.c Graph.h Hashtable.h
	gcc -c -g main.c

Graph.o:Graph.c Graph.h Hashtable.h
	gcc -c -g Graph.c

Hashtable.o: Hashtable.c Graph.h Hashtable.h
	gcc -c -g Hashtable.c



