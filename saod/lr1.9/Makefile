all: main

main: main.o service_procedures.o heapsort.o
	g++ -o main main.o service_procedures.o heapsort.o

main.o: main.cpp

service_procedures.o: service_procedures.cpp

heapsort.o: heapsort.cpp

.PHONY: clean
clean:
	rm -rf *.o