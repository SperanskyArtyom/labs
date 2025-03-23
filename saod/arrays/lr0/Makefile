all: lr1

lr1: main.o service_procedures.o
	gcc main.o service_procedures.o -o lr1

main.o: main.c

service_procedures.o: service_procedures.c

.PHONY: clean run

clean:
	rm -rf *.o lr1

run:
	./lr1
