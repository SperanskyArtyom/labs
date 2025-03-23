all: lr2

lr2: main.o selectsort.o service_procedures.o
	gcc main.o selectsort.o service_procedures.o -o lr2

main.o: main.c

graph: selectsort.o service_procedures.o graphics.o
	gcc graphics.o selectsort.o service_procedures.o -o graph

service_procedures: service_procedures.c

selectsort.o: selectsort.c

graphics.o: graphics.c

.PHONY: clean run

clean:
	rm -rf *.o
	
run:
	./lr2
