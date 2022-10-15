mymake: main.o graph.o rule.o
	gcc -g main.o graph.o rule.o -o mymake

main.o: main.c graph.h rule.h debug.h
	gcc -g -c main.c

graph.o: graph.c graph.h debug.h rule.h
	gcc -g -c graph.c

rule.o: rule.c rule.h debug.h
	gcc -g -c rule.c

clean:
	rm -rf mymake *.o