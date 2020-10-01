all: MyTime.o
	gcc -o mytime MyTime.o

MyTime.o: MyTime.c
	gcc -c MyTime.c

clean:
	rm MyTime.o
