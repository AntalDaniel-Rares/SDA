CC = gcc
CFLAGS = -std=gnu99 -g

build: ex2

ex2: split_lists.c
	$(CC) $(CFLAGS) -o $@ $^

run:
	./ex2

clean:
	rm -f ex2

exe: ex2 run
	