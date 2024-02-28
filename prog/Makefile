all: lr1 lr2 lr3 lr4 lr5 lr6 lr7 lr8

lr1: lr1.c
	gcc -o lr1 lr1.c -lm
lr2: lr2.c
	gcc -o lr2 lr2.c
lr3: lr3.cpp
	g++ -o lr3 lr3.cpp
lr4: lr4.cpp
	g++ -o lr4 lr4.cpp
lr5: lr5.cpp
	g++ -o lr5 lr5.cpp
lr6: lr6.cpp
	g++ -o lr6 lr6.cpp -lm
lr7: lr7.cpp
	g++ -o lr7 lr7.cpp
lr8: lr7.cpp
	g++ -o lr8 lr8.cpp

.PHONY: clean
clean:
	rm -rf lr*[^a-z]