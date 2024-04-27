all: table graphics

main: main.o service_procedures.o heapsort.o
	g++ -o main main.o service_procedures.o heapsort.o

table: table.o service_procedures.o heapsort.o
	g++ -o table table.o service_procedures.o heapsort.o -lsfml-graphics -lsfml-window -lsfml-system

graphics: graphics.o heapsort.o shellsort.o
	g++ graphics.o heapsort.o shellsort.o -o graphics

main.o: main.cpp

service_procedures.o: service_procedures.cpp

heapsort.o: heapsort.cpp

shellsort.o: shellsort.cpp

table.o: table.cpp

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
	./graphics