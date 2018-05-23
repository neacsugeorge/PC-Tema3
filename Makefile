GCC=gcc
FLAGS=-Wall


build: dnsclient

dnsclient: main.c src/structures.o src/connection.o src/config.o
	gcc -o $@ $^

src/structures.o: src/Structures.c src/Structures.h
	$(GCC) $(FLAGS) -c $< -o $@

src/connection.o: src/Connection.c src/Connection.h
	$(GCC) $(FLAGS) -c $< -o $@

src/config.o: src/Config.c src/Config.h
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o src/*.o dnsclient