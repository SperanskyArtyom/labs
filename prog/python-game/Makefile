all: bin/python_game

bin/python_game: obj/main.o obj/snake.o
	g++ obj/main.o obj/snake.o -o bin/python_game -lsfml-graphics -lsfml-window -lsfml-system

obj/main.o : src/python/main.cpp
	$(CC) -c src/python/main.cpp -o obj/main.o -I src
obj/snake.o : src/pythonlib/snake.cpp
	$(CC) -c src/pythonlib/snake.cpp -o obj/snake.o -I src

.PHONY: clean

clean:
	rm -rf obj/*.o