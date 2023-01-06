CC=g++
flags=-std=c++17 -Wall -pedantic
objs=obj/my_sdl.o obj/perceptron.o obj/my_random.o
dbg=-fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -g -DLOCAL
libs=-lSDL2

bin/ai.out: main.cpp $(objs)
	$(CC) $(objs) main.cpp -o bin/ai.out $(libs)

obj/my_sdl.o: include/my_sdl.h src/my_sdl.cpp
	$(CC) -c src/my_sdl.cpp -o obj/my_sdl.o

obj/perceptron.o: include/perceptron.h src/perceptron.cpp
	$(CC) -c src/perceptron.cpp -o obj/perceptron.o

obj/my_random.o: include/my_random.h src/my_random.cpp
	$(CC) -c src/my_random.cpp -o obj/my_random.o

run: bin/ai.out
	bin/ai.out

drun:
	$(CC) -c src/my_sdl.cpp -o obj/my_sdl.o $(dbg)
	$(CC) -c src/perceptron.cpp -o obj/perceptron.o $(dbg)
	$(CC) $(objs) main.cpp -o bin/ai.out $(libs) $(dbg)
	bin/ai.out
	rm bin/ai.out

clean:
	rm bin/ai.out
	rm obj/*

prepare:
	mkdir -p bin obj include src
