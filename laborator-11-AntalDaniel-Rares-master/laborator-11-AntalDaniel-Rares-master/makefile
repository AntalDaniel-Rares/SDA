CC = gcc
CFLAGS = -std=gnu99 -g

build: lab11

lab11: *.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

run:
	./lab11

clean:
	rm -f lab11

exe:
	lab11 run