all: lr3 graphics table

lr3: main.o bubblesort.o service_procedures.o
	gcc main.o bubblesort.o service_procedures.o -o lr3
table: table.o bubblesort.o service_procedures.o
	gcc table.o bubblesort.o service_procedures.o -o table
graphics: graphics.o bubblesort.o service_procedures.o
	gcc graphics.o bubblesort.o service_procedures.o -o graphics

main.o: main.c 
table.o: table.c
graphics.o: graphics.c
service_procedures.o: service_procedures.c
bubblesort.o: bubblesort.c

.PHONY: clean run graph tab
clean:
	rm -rf *.o
run: all
	clear
	./lr3
	clear
	./table
	clear
	./graphics
	./bubblesort.gpi
graph: graphics
	./graphics
	./bubblesort.gpi
tab: tab
	./table

