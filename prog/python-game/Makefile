all: main

main: obj/main.o obj/snake.o
	g++ obj/main.o obj/snake.o -o bin/python_game -lsfml-graphics -lsfml-window -lsfml-system

obj/main.o : src/python/main.cpp
	g++ -c src/python/main.cpp -o obj/main.o
obj/snake.o : src/pythonlib/snake.cpp
	g++ -c src/pythonlib/snake.cpp -o obj/snake.o

.PHONY: clean

clean:
	rm -rf obj/*.o