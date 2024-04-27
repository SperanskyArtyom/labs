all: table table2 graphics

main: main.o service_procedures.o QuickSort.o
	g++ -o main main.o service_procedures.o QuickSort.o

table: table.o service_procedures.o QuickSort.o
	g++ -o table table.o service_procedures.o QuickSort.o -lsfml-graphics -lsfml-window -lsfml-system

table2: table2.o service_procedures.o QuickSort.o
	g++ -o table2 table2.o service_procedures.o QuickSort.o -lsfml-graphics -lsfml-window -lsfml-system

graphics: graphics.o QuickSort.o
	g++ graphics.o QuickSort.o -o graphics

main.o: main.cpp

service_procedures.o: service_procedures.cpp

QuickSort.o: QuickSort.cpp

table.o: table.cpp

table2.o: table2.cpp

graphics.o: graphics.cpp

.PHONY: clean tab graph run
clean:
	rm -rf *.o

tab:
	./table

graph:
	./graphics

run:
	./table
	./table2
	./graphics