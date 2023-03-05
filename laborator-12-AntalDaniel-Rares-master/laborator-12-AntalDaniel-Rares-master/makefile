CC = gcc
CFLAGS = -std=gnu99 -g

build: lab12

lab12: *.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

run:
	./lab12

clean:
	rm -f lab12

exe:
	lab12 run