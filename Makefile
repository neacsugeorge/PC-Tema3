GCC=gcc
FLAGS=-Wall


build: dnsclient

dnsclient: main.c
	gcc -o dnsclient main.c

src/structures.o: src/Structures.c src/Structures.h
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o src/*.o dnsclient