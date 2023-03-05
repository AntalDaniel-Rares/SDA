EXEC = list

build: $(EXEC).c
	gcc $(EXEC).c -o $(EXEC) -std=gnu99

run:
	./$(EXEC)

clean:
	rm -f $(EXEC)

pack:
	zip list-lab2.zip *.c *.h Makefile

exe: build run