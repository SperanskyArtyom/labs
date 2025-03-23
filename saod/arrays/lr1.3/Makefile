all: table main

main: main.o sorts.o service_procedures.o
	g++ main.o sorts.o service_procedures.o -o main

table: table.o sorts.o service_procedures.o
	g++ table.o sorts.o service_procedures.o -o table -lsfml-graphics -lsfml-window -lsfml-system

graphics: graphics.o sorts.o
	g++ graphics.o sorts.o -o graphics

graphics.o: graphics.cpp
main.o: main.cpp
table.o: table.cpp
service_procedures.o: service_procedures.cpp
sorts.o: sorts.cpp

.PHONY: clean run graph tab
clean:
	rm -rf *.o main graphics table *.txt

tab: table
	./table

graph: graphics
	./graphics
	./graphics.gpi

run:
	clear
	./main
	./table
