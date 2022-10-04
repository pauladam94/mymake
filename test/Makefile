CC=gcc
EXEC=main
$(EXEC) : main.o c.o d.o
	$(CC) -c

a.o : a.c a.h
	$(CC) -c a.c

b.o : b.c b.h
	$(CC) -c b.c

c.o : c.c c.h a.h b.h
	$(CC) -c c.c

d.o : d.c a.h
	$(CC) -c d.c 

clean :
	rm -rf *.o $(EXEC)