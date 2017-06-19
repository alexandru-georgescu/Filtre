build:index

index.o: index.c
	gcc -c index.c

index: index.o
	gcc -Wall index.o -o index


run: index
	./index
  
clean: index 
	rm -rf index
	rm -rf index.o

