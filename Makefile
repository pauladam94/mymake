main : main.c c.o d.o
	gcc

a.o : a.c
	gcc 

b.o : b.c
	gcc

c.o : c.c a.h b.h
	gcc a.o b.o c.c

d.o : d.c a.h
	gcc a.o 