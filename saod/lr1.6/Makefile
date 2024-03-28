all: table1 table2 main graphics

main: main.o sorts.o service_procedures.o
	g++ main.o sorts.o service_procedures.o -o main

table1: table1.o sorts.o service_procedures.o
	g++ table1.o sorts.o service_procedures.o -o table1 -lsfml-graphics -lsfml-window -lsfml-system

table2: table2.o sorts.o service_procedures.o
	g++ table2.o sorts.o service_procedures.o -o table2 -lsfml-graphics -lsfml-window -lsfml-system

graphics: graphics.o sorts.o service_procedures.o
	g++ graphics.o sorts.o service_procedures.o -o graphics

graphics.o: graphics.cpp
main.o: main.cpp
table1.o: table1.cpp
table2.o: table2.cpp
service_procedures.o: service_procedures.cpp
sorts.o: sorts.cpp

.PHONY: clean run graph tab1 tab2 cleanall graph2
cleanall:
	rm -rf *.o main graphics table1 table2 *.txt graphics2 graphics3

clean:
	rm -rf *.o *.txt

run:
	clear
	./table1
	./table2
	./graphics