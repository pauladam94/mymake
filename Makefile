mymake: main.o graph.o rule.o
	gcc main.o graph.o rule.o -o mymake

main.o: main.c graph.h rule.h debug.h
	gcc -c main.c

graph.o: graph.c graph.h debug.h rule.h
	gcc -c graph.c

rule.o: rule.c rule.h debug.h
	gcc -c rule.c

clean:
	rm -rf mymake *.o