CC = gcc
CFLAGS = -std=gnu99 -g

build: ex1

ex1: inversare_prop.c
	$(CC) $(CFLAGS) -o $@ $^

run:
	./ex1

clean:
	rm -f ex1

exe:
	ex1 run