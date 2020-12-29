all: build run

build:
	gcc main.c -o main `pkg-config --cflags --libs gtk+-2.0`
run:
	./main
