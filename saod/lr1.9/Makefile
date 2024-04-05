all: main

main: main.o service_procedures.o heapsort.o
	g++ -o main main.o service_procedures.o heapsort.o

table: table.o service_procedures.o heapsort.o
	g++ -o table table.o service_procedures.o heapsort.o -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp

service_procedures.o: service_procedures.cpp

heapsort.o: heapsort.cpp

table.o: table.cpp

.PHONY: clean tab graph run
clean:
	rm -rf *.o

tab:
	./table