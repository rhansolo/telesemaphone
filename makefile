all: main.o control.o
	gcc -o main main.o
	gcc -o control control.o

main.o: main.c control.h
	gcc -c -g main.c

control.o: control.c control.h
	gcc -c -g control.c

clean:
	rm *.o
	rm *.out