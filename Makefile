output: finder.o
	g++ finder.o -o finder

finder.o: finder.cc
	g++ -c finder.cc

clean:
	rm *.o

remove:
	rm *
